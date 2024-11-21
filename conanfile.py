import os

from conan import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import CMakeToolchain, cmake_layout, CMake, CMakeDeps

class Recipe(ConanFile):
    name = "Workspace"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    tool_requires = "cmake/3.30.5"
    generators = "CMakeDeps", "CMakeToolchain"
    
    def configure(self):
        if self.settings.os == "Windows":
            self.options["tbb"].shared = True
            self.options["tbb"].tbbmalloc = True
            self.options["tbb"].tbbproxy = True

    def requirements(self):
        self.requires("zlib/1.3.1")
        self.requires("flatbuffers/24.3.25")
        self.requires("boost/1.86.0")
        self.requires("fmt/10.2.1")
        self.requires("rapidjson/cci.20230929")
        self.requires("onetbb/2021.12.0")
        self.requires("spdlog/1.14.1")
        self.requires("rapidcsv/8.84")
        self.requires("magic_enum/0.9.6")
        self.requires("libcurl/8.10.1")
        self.requires("stduuid/1.2.3")        
        self.requires("base64/0.5.2")
        self.requires("redis-plus-plus/1.3.13")
        if self.settings.os == "Linux":
            self.requires("libuuid/1.0.3")
            self.requires("odbc/2.3.11")

    def build_requirements(self):
        self.test_requires("gtest/1.15.0")


    def layout(self):
        #cmake_layout(self)
        multi = True if self.settings.get_safe("compiler") == "msvc" else False
        if multi:
            self.folders.generators = os.path.join("build", "generators")
            self.folders.build = "build"
        else:
            self.folders.generators = os.path.join("build", str(self.settings.build_type), "generators")
            self.folders.build = os.path.join("build", str(self.settings.build_type))

    def generate(self):
        #tc = CMakeToolchain(self)
        #tc.generate()

        #dp = CMakeDeps(self)
        #dp.generate()

        generate_folder = os.path.join(self.build_folder, "generators")
        toolchain_folder = os.path.join(self.recipe_folder, "ToolChain")
        print("gf:", generate_folder, "tf:", toolchain_folder)
        copy(self, "conandeps_legacy.cmake", generate_folder, toolchain_folder)
        #for dep in self.dependencies.values():
        #    c = dep.cpp_info.get_property("cmake_target_name")
        #    print("d:", c)

        #find_package와 CONAN_LIBS 변수를 담은 .cmake(툴체인)을 만들어낼 수 있다.
        #if self.settings.os == "Linux":
        #    destination = f"../build_linux/bin/{self.settings.build_type}/"
        #else:
        #    destination = f"../build_windows/bin/{self.settings.build_type}/"

        #for dep in self.dependencies.values():
        #    print("version:", dep.ref.version, "name:", dep.ref.name)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
