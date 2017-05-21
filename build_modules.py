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

    check_for_module_builder()

    cmd = [sys.executable, "-B", "-m", "voxel_native.build"]
    try:
        output = subprocess.run(cmd, stderr=sys.stderr, stdout=sys.stdout, check=True)
    except subprocess.CalledProcessError as errorMsg:
        print(errorMsg)
        print("Error building the native modules.")
        sys.exit(-1)

    shutil.move("voxel_native/voxel.pyd", "voxel.pyd")


if __name__ == "__main__":
    build_modules()
