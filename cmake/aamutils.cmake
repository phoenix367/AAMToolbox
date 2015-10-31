# get the list of subdirectories
macro(subdirlist dirlist curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(${dirlist} "")

    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND ${dirlist} ${child})
        endif()
    endforeach()
endmacro()
