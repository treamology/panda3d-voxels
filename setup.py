from setuptools import setup, find_packages
from setuptools.extension import Extension
from Cython.Build import cythonize
import numpy

extensions = [
    Extension("voxel.worldgen", ["voxel/worldgen.pyx"], include_dirs=[numpy.get_include()])
]

setup(
    name = "Panda3D Voxels",
    packages = find_packages(),
    ext_modules = cythonize(extensions)
)