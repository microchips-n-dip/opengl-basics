import os
import subprocess

class Source:
  def __init__(self):
    self.includes = []
    self.project_dir = ""
    self.target_dir = ""
    self.source = ""
    self.target = ""

  def add_includes(self, dirs):
    self.includes.extend(dirs)

  def gen_src(self):
    return os.path.join(self.project_dir, self.source)

  def gen_tgt(self):
    target_dir = os.path.join(self.project_dir, self.target_dir)
    # Create the target directory if necessary.
    if not os.path.exists(target_dir):
      subprocess.call(["mkdir", target_dir])
    return os.path.join(target_dir, self.target)

  def process(self):
    result = []
    for include in self.includes:
      result.extend(["-iquote", include])
    result.extend(["-c", self.gen_src()])
    result.extend(["-o", self.gen_tgt()])
    return result

class Project:
  def __init__(self):
    self.sources = []
    self.flags = []
    self.compile_flags = []
    self.linker_flags = []
    self.project_dir = ""
    self.target_dir = ""
    self.target = ""

  def add_flags(self, flags):
    self.flags.extend(flags)
  
  def add_compile_flags(self, flags):
    self.compile_flags.extend(flags)
  
  def add_linker_flags(self, flags):
    self.linker_flags.extend(flags)

  def add_src(self):
    new_src = Source()
    new_src.project_dir = self.project_dir
    new_src.target_dir = self.target_dir
    self.sources.append(new_src)
    return new_src

  def compile(self):
    for source in self.sources:
      cmd = []
      cmd.extend(["g++"])
      cmd.extend(self.flags)
      cmd.extend(self.compile_flags)
      cmd.extend(source.process())
      print(" ".join(cmd))
      subprocess.call(cmd)

  def gen_tgt(self):
    return os.path.join(self.project_dir, self.target)

  def link(self):
    cmd = []
    cmd.extend(["g++"])
    cmd.extend(self.flags)
    for source in self.sources:
      cmd.append(source.gen_tgt())
    cmd.extend(["-o", self.gen_tgt()])
    cmd.extend(self.linker_flags)
    print(" ".join(cmd))
    subprocess.call(cmd)

project = Project()
project.project_dir = os.getcwd()
project.target_dir = "build/"
project.target = "main"
project.add_flags(["-g", "-O2", "-march=native"])
project.add_linker_flags(["-lGL", "-lGLEW", "-lGLU", "-lSDL2"])

def construct_src(proj, name):
  src = proj.add_src()
  src.add_includes(["src/"])
  src.source = "".join(["src/", name, ".cpp"])
  src.target = "".join([name, ".o"])

def construct_lib(proj, name):
  src = proj.add_src()
  src.add_includes(["lib/"])
  src.source = "".join(["lib/", name, ".cpp"])
  src.target = "".join([name, ".o"])

construct_src(project, "main")
construct_src(project, "texture")
construct_src(project, "mesh")
construct_src(project, "shader_program")
construct_src(project, "camera")
construct_src(project, "transform")

project.compile()
project.link()
