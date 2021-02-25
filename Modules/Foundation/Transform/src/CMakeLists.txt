set(ITKFoundationTransform_SRCS
  itkTransformBase.cxx
  )

itk_module_add_library(ITKFoundationTransform ${ITKFoundationTransform_SRCS})

#[[
add_library(ITKFoundationTransform ${ITKFoundationTransform_SRCS})
itk_module_link_dependencies()
itk_module_target(ITKFoundationTransform)
]]