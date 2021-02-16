set(DOCUMENTATION "This module contains the central classes of the with KWSys & VXL
it can be used by external project without having the need to go through the ITKCommon
module compilation.")

set(BACKUP ${ITK_SOURCE_DIR})

unset(ITK_SOURCE_DIR PARENT_SCOPE)

itk_module(ITKInternal
  ENABLE_SHARED
  DEPENDS
    ${ITKCOMMON_TBB_DEPENDS}
  PRIVATE_DEPENDS
    #ITKDoubleConversion
  COMPILE_DEPENDS
    ITKKWSys
    ITKVNLInstantiation
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)

set(ITK_SOURCE_DIR ${BACKUP} PARENT_SCOPE)
unset(BACKUP)

# Extra test dependency on ITKMesh is introduced by itkCellInterfaceTest.
# Extra test dependency on ITKImageIntensity is introduced by itkImageDuplicatorTest.
# Extra test dependency on ITKIOImageBase is introduced by itkImageRandomIteratorTest22.
