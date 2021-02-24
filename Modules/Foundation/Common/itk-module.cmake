set(DOCUMENTATION "This module contains the central classes of the with KWSys & VXL
it can be used by external project without having the need to go through the ITKFoundationCommon
module compilation.")

itk_module(ITKFoundationCommon
  ENABLE_SHARED
  PRIVATE_DEPENDS
    ITKDoubleConversion
  COMPILE_DEPENDS
    ITKKWSys
    ITKVNLInstantiation
  DESCRIPTION
    "${DOCUMENTATION}"
)
