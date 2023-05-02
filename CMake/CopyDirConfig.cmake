#======================================================
# This is a macro to add a custom target to recursively copy the contents of 
# one directory to another. Files with the same contents are not copied.
# Files that don't exist in the source are deleted from the destination.

macro(add_copy_dir_command project source_dir dest_dir)

    # Find a unique name for this new target
    set(copy_target_name copy_dir_${project})
    set(copy_target_number 0)
    while (TARGET ${copy_target_name})
        math(EXPR copy_target_number, "${copy_target_number} + 1")
        set(copy_target_name copy_dir_${project}_${copy_target_number})
    endwhile()

    if(WIN32)
        add_custom_target(${copy_target_name}
            # Remove the read-only flag so we can overwrite the files
            COMMAND IF EXIST ${dest_dir} attrib ${dest_dir}/*.* -r /s   
   
            # /MIR  Copy recursively, and delete files in the destination that aren't in the source
            # /NP   Don't print progress percentage
            # /NJH  Don't print the job header
            # /NJS  Don't print the job summary
            # /NFL  Don't print the file names
            # /NDL  Don't print the directory names
            COMMAND (ROBOCOPY ${source_dir} ${dest_dir} /MIR /NP /NJH /NJS /NFL /NDL) 
            # robocopy has dumb exit codes that use values 0-7 for various flavors of success.
            # CMake treats anything other than 0 as a failure, so we need to suppress 0-7.
            # See: https://superuser.com/a/346112
                ^& IF %ERRORLEVEL% LSS 8 SET ERRORLEVEL = 0

            # Then make everything read-only again, so we don't edit the copies
            COMMAND attrib ${dest_dir}/*.* +r /s   
        )
    else()
        add_custom_target(${copy_target_name}
		    # create empty destination directories if they don't exist 
		    COMMAND mkdir -p ${dest_dir}
            # --archive Copy recursively and preserve user/group/permissions/etc.
            # --delete  Delete files in the destination that aren't in the source
            COMMAND rsync --archive --delete ${source_dir}/ ${dest_dir}/
        )
    endif()
    set_property(TARGET ${copy_target_name}    PROPERTY FOLDER copy_dir)

    add_dependencies(${project} ${copy_target_name})

endmacro(add_copy_dir_command)
#======================================================