project(ITKCommon)

#configure_file(src/itkConfigure.h.in itkConfigure.h)

set(ITKCommon_INCLUDE_DIRS
  ${ITKCommon_BINARY_DIR}
  )
set(ITKCommon_LIBRARIES ITKCommon)

itk_module_impl()

#install(FILES
  ${ITKCommon_BINARY_DIR}/itkConfigure.h
  DESTINATION ${ITKCommon_INSTALL_INCLUDE_DIR}
  COMPONENT Development
  )

# configure and install compiler feature header files
# that have fine granular support of C++11 features
# identified in a way consistent with CMake 3.1.0 and
# greater
include(CMake/itkGenerateNewCompilerFeatureDetectionHeaders.cmake)
