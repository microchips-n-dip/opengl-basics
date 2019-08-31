import os
import subprocess

# Simple cleanup routine

project_path = os.getcwd()
build_path = os.path.join(project_path, "build")
objects = os.listdir(build_path)

for object in objects:
  os.remove(os.path.join(build_path, object))

if os.path.exists(os.path.join(project_path, "vsc")):
  os.remove(os.path.join(project_path, "vsc"))

# Clear the screen

subprocess.call(["clear"])

print("All clean!")
