#ifndef RUNEXTENSIONS_H
#define RUNEXTENSIONS_H

#include "functiontraits.h"
#include "utils_global.h"

#include <QCoreApplication>
#include <QFuture>
#include <QFutureInterface>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>

#include <functional>

// hasCallOperator & Co must be outside of any namespace
// because of internal compiler error with MSVC2015 Update 2

using testCallOperatorYes = char;
using testCallOperatorNo = struct { char foo[2]; };

template<typename C>
static testCallOperatorYes testCallOperator(decltype(&C::operator()));

template<typename>
static testCallOperatorNo testCallOperator(...);

template<typename T>
struct hasCallOperator
{
    static const bool value = (sizeof(testCallOperator<T>(0)) == sizeof(testCallOperatorYes));
};

namespace Utils {
namespace Internal {

/*
   resultType<F>::type

   Returns the type of results that would be reported by a callable of type F
   when called through the runAsync methods. I.e. the ResultType in

   void f(QFutureInterface<Result> &fi, ...)
   ResultType f(...)

   Returns void if F is not callable, and if F is a callable that does not take
   a QFutureInterface& as its first parameter and returns void.
*/

template <typename Function>
struct resultType;

template <typename Function, typename Arg>
struct resultTypeWithArgument;

template <typename Function, int index, bool>
struct resultTypeTakesArguments;

template <typename Function, bool>
struct resultTypeIsMemberFunction;

template <typename Function, bool>
struct resultTypeIsFunctionLike;

template <typename Function, bool>
struct resultTypeHasCallOperator;

template <typename Function, typename ResultType>
struct resultTypeWithArgument<Function, QFutureInterface<ResultType>&>
{
    using type = ResultType;
};

template <typename Function, typename Arg>
struct resultTypeWithArgument
{
    using type = typename functionTraits<Function>::ResultType;
};

template <typename Function, int index>
struct resultTypeTakesArguments<Function, index, true>
        : public resultTypeWithArgument<Function, typename functionTraits<Function>::template argument<index>::type>
{
};

template <typename Function, int index>
struct resultTypeTakesArguments<Function, index, false>
{
    using type = typename functionTraits<Function>::ResultType;
};

template <typename Function>
struct resultTypeIsFunctionLike<Function, true>
        : public resultTypeTakesArguments<Function, 0, (functionTraits<Function>::arity > 0)>
{
};

template <typename Function>
struct resultTypeIsMemberFunction<Function, true>
        : public resultTypeTakesArguments<Function, 1, (functionTraits<Function>::arity > 1)>
{
};

template <typename Function>
struct resultTypeIsMemberFunction<Function, false>
{
    using type = void;
};

template <typename Function>
struct resultTypeIsFunctionLike<Function, false>
        : public resultTypeIsMemberFunction<Function, std::is_member_function_pointer<Function>::value>
{
};

template <typename Function>
struct resultTypeHasCallOperator<Function, false>
        : public resultTypeIsFunctionLike<Function, std::is_function<typename std::remove_pointer<typename std::decay<Function>::type>::type>::value>
{
};

template <typename Callable>
struct resultTypeHasCallOperator<Callable, true>
        : public resultTypeTakesArguments<Callable, 0, (functionTraits<Callable>::arity > 0)>
{
};

template <typename Function>
struct resultType
        : public resultTypeHasCallOperator<Function, hasCallOperator<Function>::value>
{
};

template <typename Function>
struct resultType<Function&> : public resultType<Function>
{
};

template <typename Function>
struct resultType<const Function&> : public resultType<Function>
{
};

template <typename Function>
struct resultType<Function &&> : public resultType<Function>
{
};

template <typename Function>
struct resultType<std::reference_wrapper<Function>> : public resultType<Function>
{
};
template <typename Function>
struct resultType<std::reference_wrapper<const Function>> : public resultType<Function>
{
};

/*
   Callable object that wraps a member function pointer with the object it
   will be called on.
*/

template <typename Function>
class MemberCallable;

template <typename Result, typename Obj, typename... Args>
class MemberCallable<Result(Obj::*)(Args...) const>
{
public:
    MemberCallable(Result(Obj::* function)(Args...) const, const Obj *obj)
        : m_function(function),
          m_obj(obj)
    {
    }

    Result operator()(Args&&... args) const
    {
        return ((*m_obj).*m_function)(std::forward<Args>(args)...);
    }

private:
    Result(Obj::* m_function)(Args...) const;
    const Obj *m_obj;
};

template <typename Result, typename Obj, typename... Args>
class MemberCallable<Result(Obj::*)(Args...)>
{
public:
    MemberCallable(Result(Obj::* function)(Args...), Obj *obj)
        : m_function(function),
          m_obj(obj)
    {
    }

    Result operator()(Args&&... args) const
    {
        return ((*m_obj).*m_function)(std::forward<Args>(args)...);
    }

private:
    Result(Obj::* m_function)(Args...);
    Obj *m_obj;
};

/*
   Helper functions for runAsync that run in the started thread.
*/

// void function that does not take QFutureInterface
template <typename ResultType, typename Function, typename... Args>
void runAsyncReturnVoidDispatch(std::true_type, QFutureInterface<ResultType>, Function &&function, Args&&... args)
{
    function(std::forward<Args>(args)...);
}

// non-void function that does not take QFutureInterface
template <typename ResultType, typename Function, typename... Args>
void runAsyncReturnVoidDispatch(std::false_type, QFutureInterface<ResultType> futureInterface, Function &&function, Args&&... args)
{
    futureInterface.reportResult(function(std::forward<Args>(args)...));
}

// function that takes QFutureInterface
template <typename ResultType, typename Function, typename... Args>
void runAsyncQFutureInterfaceDispatch(std::true_type, QFutureInterface<ResultType> futureInterface, Function &&function, Args&&... args)
{
    function(futureInterface, std::forward<Args>(args)...);
}

// function that does not take QFutureInterface
template <typename ResultType, typename Function, typename... Args>
void runAsyncQFutureInterfaceDispatch(std::false_type, QFutureInterface<ResultType> futureInterface, Function &&function, Args&&... args)
{
    runAsyncReturnVoidDispatch(std::is_void<typename std::result_of<Function(Args...)>::type>(),
                               futureInterface, std::forward<Function>(function), std::forward<Args>(args)...);
}

// function that takes at least one argument which could be QFutureInterface
template <typename ResultType, typename Function, typename... Args>
void runAsyncArityDispatch(std::true_type, QFutureInterface<ResultType> futureInterface, Function &&function, Args&&... args)
{
    runAsyncQFutureInterfaceDispatch(std::is_same<QFutureInterface<ResultType>&,
                                                  typename functionTraits<Function>::template argument<0>::type>(),
                                     futureInterface, std::forward<Function>(function), std::forward<Args>(args)...);
}

// function that does not take an argument, so it does not take a QFutureInterface
template <typename ResultType, typename Function, typename... Args>
void runAsyncArityDispatch(std::false_type, QFutureInterface<ResultType> futureInterface, Function &&function, Args&&... args)
{
    runAsyncQFutureInterfaceDispatch(std::false_type(),
                                     futureInterface, std::forward<Function>(function), std::forward<Args>(args)...);
}

// function, function pointer, or other callable object that is no member pointer
template <typename ResultType, typename Function, typename... Args,
          typename = typename std::enable_if<
                !std::is_member_pointer<typename std::decay<Function>::type>::value
              >::type>
void runAsyncMemberDispatch(QFutureInterface<ResultType> futureInterface, Function &&function, Args&&... args)
{
    runAsyncArityDispatch(std::integral_constant<bool, (functionTraits<Function>::arity > 0)>(),
                          futureInterface, std::forward<Function>(function), std::forward<Args>(args)...);
}

// Function = member function
template <typename ResultType, typename Function, typename Obj, typename... Args,
          typename = typename std::enable_if<
                std::is_member_pointer<typename std::decay<Function>::type>::value
              >::type>
void runAsyncMemberDispatch(QFutureInterface<ResultType> futureInterface, Function &&function, Obj &&obj, Args&&... args)
{
    // Wrap member function with object into callable
    runAsyncImpl(futureInterface,
                 MemberCallable<typename std::decay<Function>::type>(std::forward<Function>(function), std::forward<Obj>(obj)),
                 std::forward<Args>(args)...);
}

// cref to function/callable
template <typename ResultType, typename Function, typename... Args>
void runAsyncImpl(QFutureInterface<ResultType> futureInterface,
                  std::reference_wrapper<Function> functionWrapper, Args&&... args)
{
    runAsyncMemberDispatch(futureInterface, functionWrapper.get(), std::forward<Args>(args)...);
}

// function/callable, no cref
template <typename ResultType, typename Function, typename... Args>
void runAsyncImpl(QFutureInterface<ResultType> futureInterface,
                  Function &&function, Args&&... args)
{
    runAsyncMemberDispatch(futureInterface, std::forward<Function>(function),
                           std::forward<Args>(args)...);
}
/*
   AsyncJob is a QRunnable that wraps a function with the
   arguments that are passed to it when it is run in a thread.
*/

// can be replaced with std::(make_)index_sequence with C++14
template <std::size_t...>
struct indexSequence { };
template <std::size_t N, std::size_t... S>
struct makeIndexSequence : makeIndexSequence<N-1, N-1, S...> { };
template <std::size_t... S>
struct makeIndexSequence<0, S...> { typedef indexSequence<S...> type; };

template <class T>
typename std::decay<T>::type
decayCopy(T&& v)
{
    return std::forward<T>(v);
}

template <typename ResultType, typename Function, typename... Args>
class AsyncJob : public QRunnable
{
public:
    AsyncJob(Function &&function, Args&&... args)
          // decay copy like std::thread
        : data(decayCopy(std::forward<Function>(function)), decayCopy(std::forward<Args>(args))...)
    {
        // we need to report it as started even though it isn't yet, because someone might
        // call waitForFinished on the future, which does _not_ block if the future is not started
        futureInterface.setRunnable(this);
        futureInterface.reportStarted();
    }

    ~AsyncJob()
    {
        // QThreadPool can delete runnables even if they were never run (e.g. QThreadPool::clear).
        // Since we reported them as started, we make sure that we always report them as finished.
        // reportFinished only actually sends the signal if it wasn't already finished.
        futureInterface.reportFinished();
    }

    QFuture<ResultType> future() { return futureInterface.future(); }

    void run() override
    {
        if (priority != QThread::InheritPriority)
            if (QThread *thread = QThread::currentThread())
                if (thread != qApp->thread())
                    thread->setPriority(priority);
        if (futureInterface.isCanceled()) {
            futureInterface.reportFinished();
            return;
        }
        runHelper(typename makeIndexSequence<std::tuple_size<Data>::value>::type());
    }

    void setThreadPool(QThreadPool *pool)
    {
        futureInterface.setThreadPool(pool);
    }

    void setThreadPriority(QThread::Priority p)
    {
        priority = p;
    }

private:
    using Data = std::tuple<typename std::decay<Function>::type, typename std::decay<Args>::type...>;

    template <std::size_t... index>
    void runHelper(indexSequence<index...>)
    {
        // invalidates data, which is moved into the call
        runAsyncImpl(futureInterface, std::move(std::get<index>(data))...);
        if (futureInterface.isPaused())
            futureInterface.waitForResume();
        futureInterface.reportFinished();
    }

    Data data;
    QFutureInterface<ResultType> futureInterface;
    QThread::Priority priority = QThread::InheritPriority;
};

class UTILS_EXPORT RunnableThread : public QThread
{
public:
    explicit RunnableThread(QRunnable *runnable, QObject *parent = 0);

protected:
    void run();

private:
    QRunnable *m_runnable;
};

} // Internal

/*!
    The interface of \c {runAsync} is similar to the std::thread constructor and \c {std::invoke}.

    The \a function argument can be a member function,
    an object with \c {operator()} (with no overloads),
    a \c {std::function}, lambda, function pointer or function reference.
    The \a args are passed to the function call after they are copied/moved to the thread.

    The \a function can take a \c {QFutureInterface<ResultType>&} as its first argument, followed by
    other custom arguments which need to be passed to this function.
    If it does not take a \c {QFutureInterface<ResultType>&} as its first argument
    and its return type is not void, the function call's result is reported to the QFuture.
    If \a function is a (non-static) member function, the first argument in \a args is expected
    to be the object that the function is called on.

    If a thread \a pool is given, the function is run there. Otherwise a new, independent thread
    is started.

    \sa std::thread
    \sa std::invoke
    \sa QThreadPool
    \sa QThread::Priority
 */
template <typename Function, typename... Args,
          typename ResultType = typename Internal::resultType<Function>::type>
QFuture<ResultType>
runAsync(QThreadPool *pool, QThread::Priority priority, Function &&function, Args&&... args)
{
    auto job = new Internal::AsyncJob<ResultType,Function,Args...>
            (std::forward<Function>(function), std::forward<Args>(args)...);
    job->setThreadPriority(priority);
    QFuture<ResultType> future = job->future();
    if (pool) {
        job->setThreadPool(pool);
        pool->start(job);
    } else {
        auto thread = new Internal::RunnableThread(job);
        thread->moveToThread(qApp->thread()); // make sure thread gets deleteLater on main thread
        QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        thread->start(priority);
    }
    return future;
}

/*!
    Runs \a function with \a args in a new thread with given thread \a priority.
    \sa runAsync(QThreadPool*,QThread::Priority,Function&&,Args&&...)
    \sa QThread::Priority
 */
template <typename Function, typename... Args,
          typename ResultType = typename Internal::resultType<Function>::type>
QFuture<ResultType>
runAsync(QThread::Priority priority, Function &&function, Args&&... args)
{
    return runAsync(static_cast<QThreadPool *>(nullptr), priority,
                    std::forward<Function>(function), std::forward<Args>(args)...);
}

/*!
    Runs \a function with \a args in a new thread with thread priority QThread::InheritPriority.
    \sa runAsync(QThreadPool*,QThread::Priority,Function&&,Args&&...)
    \sa QThread::Priority
 */
template <typename Function, typename... Args,
          typename = typename std::enable_if<
                !std::is_same<typename std::decay<Function>::type, QThreadPool>::value
                && !std::is_same<typename std::decay<Function>::type, QThread::Priority>::value
              >::type,
          typename ResultType = typename Internal::resultType<Function>::type>
QFuture<ResultType>
runAsync(Function &&function, Args&&... args)
{
    return runAsync(static_cast<QThreadPool *>(nullptr),
                    QThread::InheritPriority, std::forward<Function>(function),
                    std::forward<Args>(args)...);
}

/*!
    Runs \a function with \a args in a thread \a pool with thread priority QThread::InheritPriority.
    \sa runAsync(QThreadPool*,QThread::Priority,Function&&,Args&&...)
    \sa QThread::Priority
 */
template <typename Function, typename... Args,
          typename = typename std::enable_if<
                !std::is_same<typename std::decay<Function>::type, QThread::Priority>::value
              >::type,
          typename ResultType = typename Internal::resultType<Function>::type>
QFuture<ResultType>
runAsync(QThreadPool *pool, Function &&function, Args&&... args)
{
    return runAsync(pool, QThread::InheritPriority, std::forward<Function>(function),
                    std::forward<Args>(args)...);
}

} // Utils

#endif // RUNEXTENSIONS_H