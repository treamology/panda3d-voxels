from setuptools import setup, find_packages
from Cython.Build import cythonize

setup(
    name = "Panda3D Voxels",
    packages = find_packages(),
    ext_modules = cythonize([])
)