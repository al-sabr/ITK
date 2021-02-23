set(ITKFoundationCommon_SRC
  itkNumericTraits.cxx
  itkIndent.cxx
  itkEventObject.cxx
  itkNumericTraitsVectorPixel.cxx
  itkObject.cxx
  itkProcessObject.cxx
  itkRealTimeInterval.cxx
  itkNumericTraitsFixedArrayPixel.cxx
  itkMetaDataObject.cxx
  itkMetaDataDictionary.cxx
  itkDataObject.cxx
  itkCommand.cxx
  itkNumericTraitsPointPixel.cxx
  itkLightObject.cxx
  itkRegion.cxx
  itkImageIORegion.cxx
  itkImageRegionSplitterBase.cxx
  itkImageRegionSplitterSlowDimension.cxx
  itkVersion.cxx
  itkMetaDataObjectBase.cxx
  itkProgressReporter.cxx
  itkExceptionObject.cxx
  itkVector.cxx
  itkRealTimeStamp.cxx
  itkDirectory.cxx
  itkTimeStamp.cxx
  itkObjectFactoryBase.cxx
  itkOutputWindow.cxx
  itkSimpleFastMutexLock.cxx
  itkSmartPointerForwardReferenceProcessObject.cxx
  itkThreadPool.cxx
  itkMath.cxx
  )

if(WIN32)
  list(APPEND ITKFoundationCommon_SRC itkWin32OutputWindow.cxx)
endif()

if(ITK_USE_WIN32_THREADS)
  list(APPEND ITKFoundationCommon_SRC itkThreadPoolWin32.cxx)
elseif(ITK_USE_PTHREADS)
  list(APPEND ITKFoundationCommon_SRC itkThreadPoolPosix.cxx)
endif()

if(ITK_DYNAMIC_LOADING)
  list(APPEND ITKFoundationCommon_SRC itkDynamicLoader.cxx)
endif()

# Prevent optimization from affecting the floating point calculation.
if( CMAKE_CXX_COMPILER MATCHES "^icc" )
  if( WIN32 )
    set_source_files_properties( itkCompensatedSummation.cxx PROPERTIES COMPILE_FLAGS /fp precise )
  else()
    set_source_files_properties( itkCompensatedSummation.cxx PROPERTIES COMPILE_FLAGS -fp-model precise )
  endif()
elseif( CMAKE_COMPILER_IS_GNUCXX )
  # -fno-associative-math appears to only be present in GCC 4.3 onwards.
  include( CheckCXXCompilerFlag )
  CHECK_CXX_COMPILER_FLAG( -fno-associative-math gcc_has_no_associative_math )
  if( gcc_has_no_associative_math )
    set_source_files_properties( itkCompensatedSummation.cxx PROPERTIES COMPILE_FLAGS -fno-associative-math )
  else()
    set_source_files_properties( itkCompensatedSummation.cxx PROPERTIES COMPILE_FLAGS -fno-unsafe-math-optimizations )
  endif()
elseif( MSVC )
  set_source_files_properties( itkCompensatedSummation.cxx PROPERTIES COMPILE_FLAGS -fp:precise )
endif()

if( CMAKE_CXX_COMPILER_ID MATCHES Clang AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.0" )
  # this file contains explicitly instantiated template classes which are not correcly exported with the hidden visibility flag
  set_source_files_properties( itkSmartPointerForwardReferenceProcessObject.cxx PROPERTIES COMPILE_FLAGS -fvisibility=default )
endif()


### generating libraries
itk_module_add_library( ITKFoundationCommon ${ITKFoundationCommon_SRC})

target_link_libraries(ITKFoundationCommon LINK_PUBLIC itksys ITKVNLInstantiation)

if(UNIX)
  target_link_libraries(ITKFoundationCommon LINK_PUBLIC ${CMAKE_THREAD_LIBS} -lm)
  if(ITK_DYNAMIC_LOADING)
    target_link_libraries(ITKFoundationCommon LINK_PUBLIC ${CMAKE_DL_LIBS})
  endif()
endif()
