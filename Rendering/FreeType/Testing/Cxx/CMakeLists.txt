# Check that matplotlib is available
include(FindPythonModules)
find_python_module(matplotlib MATPLOTLIB_FOUND)

if(NOT MATPLOTLIB_FOUND)
  message(STATUS "Matplotlib not found! MathText rendering will not be available until it is installed. Disabling tests.")
endif()

# add tests that do not require data or produce vector output
set(TestMathTextFreeTypeTextRendererNoMath_ARGS
  DATA{../Data/Fonts/DejaVuSans.ttf}
)
vtk_add_test_cxx(TestMathTextFreeTypeTextRendererNoMath.cxx)

set(TestFreeTypeTextMapperNoMath_ARGS DATA{../Data/Fonts/DejaVuSans.ttf})
vtk_add_test_cxx(TestFreeTypeTextMapperNoMath.cxx)

# add tests that require data
vtk_add_test_cxx(TestFTStringToPath.cxx)

if(MATPLOTLIB_FOUND)
  set(TestMathTextFreeTypeTextRenderer_ARGS DATA{../Data/Fonts/DejaVuSans.ttf})
  vtk_add_test_cxx(TestMathTextFreeTypeTextRenderer.cxx)

  set(TestFreeTypeTextMapper_ARGS DATA{../Data/Fonts/DejaVuSans.ttf})
  vtk_add_test_cxx(TestFreeTypeTextMapper.cxx)
endif()

# This benchmark takes a while to run and can't fail, so disable it by default:
option(VTK_BUILD_FREETYPE_BENCHMARK
  "Build a BenchmarkFreeTypeRendering test that benchmarks freetype rendering performance."
  OFF)
mark_as_advanced(VTK_BUILD_FREETYPE_BENCHMARK)

if(VTK_BUILD_FREETYPE_BENCHMARK)
  vtk_add_test_cxx(BenchmarkFreeTypeRendering.cxx NO_VALID)
endif()

vtk_test_cxx_executable(${vtk-module}CxxTests RENDERING_FACTORY)
