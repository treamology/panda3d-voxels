import os, sys, subprocess, shutil
import argparse

def build_modules():
    print("Building native modules...")
    
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--debug", action="store_true", help="Builds a debug module")
    parser.add_argument(
        "--panda-path", type=str, help="Where the Panda3D libraries are located")
    args = parser.parse_args()

    os.chdir(os.path.split(os.path.realpath(__file__))[0])
    
    cmd = [sys.executable, "-B", "-m", "P3DModuleBuilder.build", "--source-dir", "../native", "--output-dir", "../"]
    
    if args.debug:
        cmd += ["--optimize", "1"]
    if args.panda_path:
        cmd += ["--panda-path", args.panda_path]
    
    try:
        output = subprocess.run(cmd, stderr=sys.stderr, stdout=sys.stdout, check=True)
    except subprocess.CalledProcessError as errorMsg:
        print(errorMsg)
        print("Error building the native modules.")
        sys.exit(-1)

if __name__ == "__main__":
    build_modules()
