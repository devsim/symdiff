import os
import re
from glob import glob
from setuptools import Distribution, setup

#https://stackoverflow.com/questions/35112511/pip-setup-py-bdist-wheel-no-longer-builds-forced-non-pure-wheels/36886459#36886459
#https://stackoverflow.com/questions/24071491/how-can-i-make-a-python-wheel-from-an-existing-native-library/24793171#24793171

wheel_abi = os.environ.get("SYMDIFF_WHEEL_ABI", "abi3")
if wheel_abi not in ("abi3", "abi3t"):
    raise ValueError(f"Unsupported SYMDIFF_WHEEL_ABI: {wheel_abi}")

cmdclass = {}
if wheel_abi == "abi3t":
    from setuptools.command.bdist_wheel import bdist_wheel

    class Abi3tWheel(bdist_wheel):
        def get_tag(self):
            _, _, platform = super().get_tag()
            return "cp315", "abi3t", platform

    cmdclass["bdist_wheel"] = Abi3tWheel


class BinaryDistribution(Distribution):
    """Distribution which always forces a binary package with platform name"""
    def has_ext_modules(foo):
        return True

    def is_pure(self):
        return False


def fix_readme(text):
    regex = re.compile('\[([^]]+)\]+\((?!http[s]:\/\/)([^)]+)\)')
    base_url = os.environ.get('README_BASE_URL')
    if base_url:
        if base_url[-1] != '/':
            base_url += '/'
        print("Fixing up base url for long description {0}".format(base_url))
        text = regex.sub(lambda m, urlbase=base_url : r'[{0}]({1})'.format(m.group(1), urlbase + m.group(2)), text)
    return text

with open('README.md', 'r') as ifile:
    text = ifile.read()
    text = fix_readme(text)

setup(
      distclass=BinaryDistribution,
      data_files = [
        ('symdiff_data',  ['LICENSE', 'NOTICE', 'README.md',]),
        ('symdiff_data/doc', glob('doc/*.pdf')),
        ('symdiff_data/examples', glob('examples/*.*')),
      ],
      long_description = text,
      long_description_content_type="text/markdown",
      cmdclass=cmdclass,
      options={"bdist_wheel": {"py_limited_api": "cp39" if wheel_abi == "abi3" else "cp315"}},
    )
