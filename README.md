# Bytes

효율적으로 네트워크 I/O 처리를 위한 버퍼 기능을 포함합니다.


## 구성

### CMake

CMake는 빌드 시스템에서 필요로 하는 파일을 생성하기 위한 도구 입니다. 현재 CMake는 3.30 이상 버전을 사용 합니다.



### Conan

3rd Party 라이브러리에 대한 의존성 관리와 CMake 빌드 환경을 위해 [conan 2](https://docs.conan.io/2/index.html)을 사용하고 있습니다.  Root 디렉토리에 `conanfile.py`를 통해 의존성을 관리하고 있으며, 해당 파일을 통해 `conan install`을 실행하면 빌드 환경에 필요한 `CMakePresets.json`과 `CMake Toolchain`이 제공됩니다. 



### Clang-Format

일관된 코딩 스타일을 유지하기 위해 코드 포메터인 Clang-Format을 사용하며 이를 위해 `.clang-format` 를 제공합니다. 또한 `Docs`디렉토리에 컨벤션 문서를 제공하고 있습니다.



## 설치

### Conan

Multiple Configurations 개발 환경(Debug, Release)을 위해 `conanfile.py`가 있는 디렉토리에서 다음 명령을 실행합니다.

```powershell
conan install . --build=missing --settings=build_type=Debug
conan install . --build=missing --settings=build_type=Release
```

이렇게 명령을 실행하면 `./build/generators` 디렉토리에 `CMakePresets.josn` 및 `conan_toolchain.cmake` 그리고 `Find<Package>.cmake`, `<Package>Config.cmake`등의 파일이 생성됩니다. 또한 해당 파일들을 바로 Root 디렉토리에서 참조할 수 있도록 Root 디렉토리에 `CMakeUserPresets.json`이 생성됩니다.

> **Conan을 처음 설치한 경우**
>
> conan install 시 "ERROR: The default build profile `~/.conan2/profiles/default` doesn't exist."와 같은 에러가 발생했다면, 자신의 작업 환경에 맞는 default profile을 생성하지 않아서 입니다. 이 경우 다음과 같이 `conan profile` 명령을 통해 기본 프로파일을 생성해줘야 합니다.
>
> ```pwoershell
> conan profile detect
> ```
>
> 보다 자세한 사항은 [여기](https://docs.conan.io/2/reference/commands/profile.html)를 참고해주세요.



### IDE 환경: VSCode 

#### CMake 설치 및 빌드

CMake 사용을 위해 마켓플레이스에서 확장을 설치합니다.

- C/C++ Extension Pack
- CMake Language Support (선택)

확장 설치가 완료되었다면 다음에 따라 진행합니다.

- `[파일] -> [폴더 열기]` 선택 후 프로젝트 열기
- 팔래트(`Shift + Ctrl + P`)를 열어 `CMake: Select Configure Preset`을 선택
- `conan-default`를 선택
- 팔래트(`Shift + Ctrl + P`)를 열어 `CMake: Select Build Preset`을 선택
- `conan-debug` 또는 `conan-release` 선택
- 팰래트(`Shift + Ctrl + P`)를 열어 `CMake: Build` 또는 `CMake: Debug` 실행



#### Clang-Format 설치 및 사용

Clang-Format 사용을 위해 마켓플레이스에서 확장을 설치합니다.

- Clang-Format

확장 설치가 완료되었다면 다음에 따라 진행합니다.

- `[파일]` -> `[기본 설정]` -> `[설정]` 을 선택

- `사용자` 탭 -> `확장` -> `Clang-Format configuration` 선택

- `Executable 설정에 다음과 같이 clang-format 실행 파일 경로 설정

  > ${workspaceRoot}\Tool\Clang-Format\Bin\Windows\clang-format.exe

- 소스 파일 코드 변경 후 저장



## FAQ

### 1) Conan 설치 시 SSL Certification 에러 발생

`conan install .` 명령 실행 시 `SSL Certification`에러가 발생하는 경우가 종종 있습니다. 회사 방화벽 이슈 또는 인증서 갱신이 제대로 되어 있지 않아 발생할 수 있습니다. 여기서는 간단하게 SSL 인증을 비활성화하여 해당 문제를 우회할 수 있는 방법을 제공합니다.

일단 conan 설정 파일 및 의존성 데이터가 관리되는 `.conan2`디렉토리로 이동합니다.

```powershell
cd ~/.conan2
```

해당 디렉토리에는 다음과 같은 디렉토리 및 파일이 존재합니다.

```powershell
.
  |_ extensions
  |_ migrations
  |_ p
  |_ profiles
  |_ global.conf
  |_ remotes.json
  |_ settings.yml
  |_ version.txt
```

SSL 인증을 우회하기 위해서는 일단 `remotes.json`을 열고 다음과 같이 `"verify_ssl": false` 수정합니다. 이를 통해 conancenter를 통해 다운로드 할 경우 SSL 인증을 비활성화 할 수 있습니다.

```json
{
 "remotes": [
  {
   "name": "conancenter",
   "url": "https://center.conan.io",
   "verify_ssl": false 
  }
 ]
}
```

다음으로 실제 코드를 다운로드하여 빌드해야 하는 경우가 존재하는데 이 경우 각 주소를 모두 확인하여 처리하기 힘들기 때문에 `global.conf`에 `tools.files.download:verify = False`를 추가하여 SSL 인증을 비활성화 합니다.

```ini
# Core configuration (type 'conan config list' to list possible values)
# e.g, for CI systems, to raise if user input would block
# core:non_interactive = True
# some tools.xxx config also possible, though generally better in profiles
# tools.android:ndk_path = my/path/to/android/ndk

tools.files.download:verify = False
```

이후 `conan install .`을 실행하여 정상여부를 확인하시면 됩니다.



### 2) conan 의존성 캐시를 모두 제거하려면 어떻게 해야하나요?

conan 캐시 초기화를 위해서는 다음 명령을 실행합니다.

```powershell
conan remove "*" -c
```



### 3) cmake를 통해 직접 빌드하려면 어떻게 해야 하나요?

이용 가능한 `Configuration Presets`를 조회 합니다.

```powershell
cmake --list-presets
```

결과: `conan install`에 의해 생성된 `conan-default`가 출력됩니다.

```
Available configure presets:

  "conan-default" - 'conan-default' config
```

다음으로 이용 가능한 `Build Presets`를 조회합니다.

```powershell
cmake --build --list-presets
```

결과: `conan install`에 의해 생성된 `conan-debug`와 `conan-relese`가 출력됩니다.

```
Available build presets:

  "conan-debug"       
  "conan-release" 
```

정보를 확인했다면 다음 명령을 통해 빌드할 수 있습니다.

```
cmake --build --preset <build preset>
```

`conan-debug`와 `conan-release` 빌드를 위한 명령은 다음과 같습니다.

```powershell
cmake --build --preset conan-debug
cmake --build --preset conan-release
```



## 참고

- [CMake 튜토리얼](https://gist.github.com/luncliff/6e2d4eb7ca29a0afd5b592f72b80cb5c#cmake-%EB%B0%B0%EC%B9%98)
- [Conan 2](https://docs.conan.io/2/)
- [CMake Preset Build](https://mcuoneclipse.com/2023/12/03/building-with-cmake-presets/)

