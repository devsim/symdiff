from setuptools import setup, Distribution
from glob import glob

#https://stackoverflow.com/questions/35112511/pip-setup-py-bdist-wheel-no-longer-builds-forced-non-pure-wheels/36886459#36886459
#https://stackoverflow.com/questions/24071491/how-can-i-make-a-python-wheel-from-an-existing-native-library/24793171#24793171
class BinaryDistribution(Distribution):
    """Distribution which always forces a binary package with platform name"""
    def has_ext_modules(foo):
        return True

setup(
      packages=['symdiff',],
      package_data={
        'symdiff' : ['./*.so', './*.dll', './*.dylib', './*.pyd',],
      },
      distclass=BinaryDistribution,
      data_files = [
        ('symdiff_data',  ['LICENSE', 'NOTICE', 'README.md',]),
        ('symdiff_data/doc', glob('doc/*.pdf')),
        ('symdiff_data/examples', glob('examples/*.*')),
      ],
    )
