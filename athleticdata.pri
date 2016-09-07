# Usage: Define variables (details below) and include this pri file afterwards.
#
# STATIC_BASE         - base directory for the files listed in STATIC_FILES
# STATIC_FILES        - list of files to be deployed
# STATIC_OUTPUT_BASE  - base directory in the compile output
# STATIC_INSTALL_BASE - base directory in the install output

# used in custom compilers which just copy files
defineReplace(stripStaticBase) {
	return( $$section(1, /, -2, -1))
#	return($$relative_path($$1, $$STATIC_BASE))
#	return($$relative_path($$absolute_path($$1, $$STATIC_OUTPUT_BASE), $$STATIC_BASE))
}

# handle conditional copying based on STATIC_BASE compared to STATIC_OUTPUT_BASE
!isEmpty(STATIC_FILES) {
	isEmpty(STATIC_BASE): \
		error("Using STATIC_FILES without having STATIC_BASE set")
	isEmpty(STATIC_OUTPUT_BASE): \
		error("Using STATIC_FILES without having STATIC_OUTPUT_BASE set")
	!osx:isEmpty(STATIC_INSTALL_BASE): \
		error("Using STATIC_FILES without having STATIC_INSTALL_BASE set")

	!isEqual(STATIC_BASE, $$STATIC_OUTPUT_BASE) {
message(" --- " $$STATIC_FILES)
		copy2build.input += STATIC_FILES
		copy2build.output = $$STATIC_OUTPUT_BASE/${QMAKE_FUNC_FILE_IN_stripStaticBase}
#		copy2build.output = ${QMAKE_FUNC_FILE_IN_stripStaticBase}
		isEmpty(vcproj):copy2build.variable_out = PRE_TARGETDEPS
		win32:copy2build.commands = $$QMAKE_COPY \"${QMAKE_FILE_IN}\" \"${QMAKE_FILE_OUT}\"
		unix:copy2build.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
		copy2build.name = COPY ${QMAKE_FILE_IN}
		copy2build.config += no_link
#		copy2build.CONFIG += no_clean
		QMAKE_EXTRA_COMPILERS += copy2build
	}

	!isEmpty(STATIC_INSTALL_BASE){
		static.files = $$STATIC_FILES
		static.base = $$STATIC_BASE
		static.path = $$STATIC_INSTALL_BASE
		INSTALLS += static
	}
}
