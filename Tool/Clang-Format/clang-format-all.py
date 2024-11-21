import os
import glob
import subprocess
import platform

root_dir = "."
include_dir = ["Common/**", "Components/**", "Launcher/**", "Tests/**", "Tool/Sgsp/bin/template/**"]
exclude_dir = ["Common/**/External/**", "Tests/Source/Protocol/FastBinaryEncoding/**"]
include_file = ["*.h", "*.cpp"]

if platform.system() == "Windows":
    clang_format = f"{root_dir}/Tool/Clang-Format/Bin/Windows/clang-format.exe"
else:
    clang_format = f"{root_dir}/Tool/Clang-Format/Bin/Linux/clang-format"


def isExecutable(name):
    """Check whether `name` is on PATH and marked as executable."""

    # from whichcraft import which
    from shutil import which

    return which(name) is not None

def getFileList(root_dir, include_dir, exclude_dir, include_file):

    # include file set
    include_file_set = set()
    for d in include_dir:
        for f in include_file:
            include_file_set.update(glob.glob(f"{root_dir}/{d}/{f}", recursive=True))

    # exclude file set
    exclude_file_set = set()
    for d in exclude_dir:
        for f in include_file:
            exclude_file_set.update(glob.glob(f"{root_dir}/{d}/{f}", recursive=True))

    # replace separator. windows to linux
    if os.path.sep == "\\":
        include_file_set = set(map(lambda x:x.replace("\\", "/"), include_file_set))
        exclude_file_set = set(map(lambda x:x.replace("\\", "/"), exclude_file_set))

    # 
    include_file_set = include_file_set - exclude_file_set

    # sort list
    result_list = list(include_file_set)
    result_list.sort()

    return result_list

if not isExecutable(clang_format):
    print(f"{clang_format} is not executable")
    exit()

target_files = getFileList(root_dir=root_dir, include_dir=include_dir, exclude_dir=exclude_dir, include_file=include_file)
for f in target_files:
    print(f'"{clang_format}" -i --style=file {f}')
    subprocess.call([clang_format, "-i", "--style=file", f])
