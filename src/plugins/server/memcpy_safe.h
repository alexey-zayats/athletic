#ifndef MEMCPY_SAFE_H
#define MEMCPY_SAFE_H

// TODO: use the windows function on windows

inline void* memcpy_safe(void* destination, size_t destinationSize, const void* source, size_t count)
{
    Q_ASSERT(destinationSize >= count);
    if(destinationSize < count)
    {
        return 0;
    }
    return ::memcpy(destination, source, count);
}
#endif // MEMCPY_SAFE_H
