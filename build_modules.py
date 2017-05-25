import os, sys, subprocess, shutil

def check_for_module_builder():
    if os.path.exists("voxel_native/scripts/"):
        return

    print("Downloading P3DModuleBuilder...")

    cmd = [sys.executable, "-B", "voxel_native/download_P3DModuleBuilder.py"]
    try:
        output = subprocess.check_output(cmd, stderr=sys.stderr)
    except subprocess.CalledProcessError as errorMsg:
        print(errorMsg)
        print("Couldn't download P3DModuleBuilder.")
        sys.exit(-1)

def build_modules():
    print("Building native modules...")

    os.chdir(os.path.split(os.path.realpath(__file__))[0])
    check_for_module_builder()

    cmd = [sys.executable, "-B", "-m", "voxel_native.build"]
    try:
        output = subprocess.run(cmd, stderr=sys.stderr, stdout=sys.stdout, check=True)
    except subprocess.CalledProcessError as errorMsg:
        print(errorMsg)
        print("Error building the native modules.")
        sys.exit(-1)

    from voxel_native.scripts.common import is_macos, is_windows, is_linux
    if is_windows():
        shutil.move("voxel_native/voxel_native.pyd", "voxel/voxel_native.pyd")
    elif is_macos() or is_linux():
        shutil.move("voxel_native/voxel_native.so", "voxel/voxel_native.so")

if __name__ == "__main__":
    build_modules()
