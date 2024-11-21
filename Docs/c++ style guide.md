---
layout: post
title: "c++ style guide"
date: 2022-08-25 18:00:00 +0900
author: 권상택

category: 개발표준
tags:
  - c++
use_toc: true
---

>#### Notice
>
> SGE 개발 기술 담당 서버
>
> 팀 프로젝트의 코드 가독성을 높이고 일관된 코드 품질을 유지하기 위해 작성된 문서입니다. 해당 문서는 Google C++ Style Guide를 기반으로 작성되었습니다.
{: .block-tip }

## 파일 및 디렉토리 

파일 이름은 대문자로 시작하여 각 단어의 첫 글자를 대문자로 쓰고, 언더스코어는 사용하지 않는다. 헤더파일은 .h로 끝나며 C++ 파일은 .cpp로 끝난다.

```cpp
// 헤더 파일
MyCalss.h

// C++ 파일
MyCalss.cpp
```

디렉토리 이름은 대문자로 시작하여 각 단어의 첫 글자를 대문자로 쓰고, 언더스코어는 사용하지 않는다.

```
c:\Workspace\sgsp\include> dir /A:D
2022-06-07 오후 03:24 <DIR> .
2022-06-07 오후 03:24 <DIR> ..
2022-06-07 오후 03:24 <DIR> Utility
2022-06-07 오후 03:24 <DIR> Interfaces
2022-06-07 오후 03:24 <DIR> Parser
```

파일 인코딩은 UTF8을 사용합니다. 프로젝트 최상위 폴더에 .editorconfig 내용은 아래와 같습니다.

```cpp
[*]
charset = utf-8
indent_style = tab
```


## 가드 규칙

같은 헤더파일이 여러번 포함되는 것을 방지하기 위해 위해 `#define` 가드를 사용한다. 기호의 포맷은 `<SOLUTION>_<PROJECT>_<PATH>_<FILE>_H_` 으로 한다. 예를 들어  `SGSP` 솔루션에 `Network`프로젝트가 있고, `Network` 프로젝트에 `Network.h` 파일이 존재할 경우 다음과 같이 작성한다.

```cpp
#ifndef SGSP_NETWORK_NETWORK_H_
#define SGSP_NETWORK_NETWORK_H_

// TODO: 작업 ...

#endif // end SGSP_NETWORK_NETWORK_H_
```

프로젝트에 포함되지 않는 코드는 프로젝트 자리를 비워둔다. 기호의 포맷은 `<SOLUTION>__<PATH>_<FILE>_H_`와 같다. 예를 들어 `SGSP` 솔루션에 Include 디렉토리에 `time.h` 파일이 존재할 경우 다음과 같이 작성한다.

```cpp
#ifndef SGSP__TIME_H_
#define SGSP__TIME_H_

// TODO: 작업 ...

#endif // end SGSP__TIME_H_
```



## 탭

 탭은 4스페이스로 지정한다.

```cpp
void Func() {
    // space 4
}
```



## 주석

### 기본

주석은 우리가 작성한 코드를 나 또는 다른 누군가가 읽고 이해 할 수 있도록 작성되어야 한다. 주석 작성 시 `//` 문법과 `/* */` 문법이 있으나 더 일반적으로 사용되는 `//` 문법을 사용하도록 한다.



#### 파일 주석

파일 주석은 파일에 담겨 있는 내용을 요약해줘야 한다. 해당 내용에는 코드의 주요 쓰임새와 어떤 독자를 의도하고 만든 코드인지를 명시한다. 일반적으로 한두 문단으로 간결하게 설명해야 하지만 그렇지 않을 경우 API를 여러 조각으로 쪼개는 방안을 검토해봐야 한다.

```cpp
// str_cat.h
// 
// This header file contains functions for efficiently concatenating and appending 
// strings: StrCat() and StrAppend(). Most fo the work within these routines is 
// actually handled through use of a special AlphaNum type, which was designed 
// to be used as a parameter type that efficiently manages conversion to 
// strings and avoids copies in the above operations.
```



#### 클래스(구조체) 주석

모든 공개 클래스와 구조체는 클래스 주석을 담고 있어야 한다. 클래스 주석에서는 해당 클래스와 주석의 목적과 주요 메서들을 설명한다. 클래스 주석은 보통 '객체'임을 부각하기 위해 클래스 자신을 문장의 주어로 두고 어떻게 동작하는지를 설명하는 형태로 작성한다. 예를 들어 "Foo 클래스는 x, y, z 속성을 가지며, A라는 기능을 제공 하고, 다음과 같이 B라는 측면을 지니고 있습니다." 처럼 작성한다.

```cpp
// AlphaNum
//
// The AlphaNum class acts as the main paraemter type  for StrCat() and 
// StrAppend(), providing efficient conversion of numeric, boolean, and 
// hexadecimal values (through the Hex type) into strings.
```



#### 함수(메서드) 주석

전역함수나 클래스의 공개 메서드에는 무조건 함수(메서드)가 무슨 일을 하는지를 설명하는 함수 주석이 있어야 한다. 함수 주석은 함수가 무슨 동작을 하고 무엇을 반환하는지를 설명하며, 능동성을 부각하기 위해 동사로 시작해야 한다.

```cpp
// StrCat()
//
// Merges the given strings or numbers, using no delimiter(s),
// returning the merged result as a string.
```



### Doxygen

Doxygen 주석은 주석 기본 사용 스타일과 일관성을 유지하기 위해 3개의 슬래시(`///`)를 사용하며, 명령은 `@(앳 마크)`를 사용한다. 

> Doxygen 주석은 일반 주석 규칙과 다르게 설명에 모든 내용을 포함하지 않고 명령 별로 내용을 구분하여 작성해야한다. 

```cpp
/// @brief 간략 설명
/// @details 상세한 설명 
```

Doxygen 주석 사용 시 다음과 같이 첫 줄과 마지막 줄에 빈 주석을 사용해서는 안된다.

```cpp
/// <--- 빈 주석(X)
/// @brief 간략 설명
/// @details 상세한 설명 
/// <--- 빈 주석(X)
```



#### 각 항목 별 추가 사용 가능한 명령

각 항목별 기본 명령 이후에 추가 가능한 명령들이다.

| No.  | 명령                                   | 비고                                                |
| ---- | -------------------------------------- | --------------------------------------------------- |
| 1    | @note {text}                           | 추가적으로 공유해야할 내용을 작성한다.              |
| 2    | @pre {description of the precondition} | 사전 조건 등이 존재하는 경우 작성한다.              |
| 3    | @bug {bug description}                 | 해당 버전에 알려진 버그가 있을 경우 작성한다.       |
| 4    | @warning {warning message}             | 사용시 주의 사항이 있을 경우 작성한다.              |
| 5    | @see {references}                      | 관련되어 있는 클래스, 함수 등이 있을 경우 작성한다. |



#### 파일 주석

파일 주석은 기본적으로 파일 첫 라인에 위치하며, 파일에 담겨 있는 내용을 요약한다. 작성 요령은 기본 주석 작성 요령과 동일하다.

##### Command 정의 순서

| No.  | 명령                            | 비고                                                         |
| ---- | ------------------------------- | ------------------------------------------------------------ |
| 1    | @file [<name>]                  | 파일 이름을 추가한다.                                        |
| 2    | @brief {brief description}      | 간단한 내용을 작성한다.                                      |
| 3    | @details {detailed description} | 상세한 내용을 작성한다.                                      |
| 4    | @author {list of authors}       | 작성자 이름과 이메일 정보를 추가해야 한다.<br />만일 작성자가 여럿일 경우 @author을 <br />여러 줄로 작성 가능하다. |
| 5    | @date {date description}        | YYYY-DD-MM 형식을 사용하며, 날짜 뒤에 <br />수정 내용을 작성 가능합니다. 만일<br />여러개를 작성해야 할 경우 @date를 여러 줄로<br />작성 가능하다. |

#### 작성 예시

StringTokenizer 클래스가 있다고 가정하고 내용을 작성한다.

```cpp
/// @file StringTokenizer.h
/// @brief 문자열 토큰링을 위한 클래스를 포함하고 있습니다.
/// @details  
/// 이 파일은 문자열 토큰링을 위한 클래스와 이를 돕기 위한 헬퍼 클래스들을 포함하고 있습니다. 문자열 토큰링 최적화를 위해
/// 전체 문자열 순회를 최소화하였으며, 토큰링된 문자열을 저장할 때 깊은 복사 대신 얕은 복사를 수행하도록 작성하였습니다. 또한 
/// 사용성을 높이기 위해 std::vector를 상속하여 stl 호환성을 높였습니다.
/// @author OOOOOO (OOOOOO@smilegate.com)
/// @date 2023-02-27 StringTokenizer.h 생성
```

 

####네임스페이스 주석

모든 파일에 네임스페이스가 사용되고 있으므로, 모든 파일에 네임스페이스 주석을 추가할 경우 생성된 문서에 중복된 내용이 표시되는 이슈가 존재한다. 이를 해결하기 위해 네임 스페이스 주석 관리가 필요한 프로젝트는 루트 디렉토리에 `NamespaceForDoxygen.h`를 생성하여 네임 스페이스 주석을 관리한다.

##### Command 정의 순서

| No.  | 명령                       | 비고 |
| ---- | -------------------------- | ---- |
| 1    | @brief {brief description} |      |

##### 작성 예시

`NamespaceForDoxygen.h` 파일 작성 내용

```cpp
/// @brief Root Namespace
namespace sgsp {
} // namespace sgsp

/// @brief 유틸리티 관리를 위한 네임스페이스
namespace sgsp::utility {
} // namespace sgsp::utility
```



#### 클래스(구조체) 주석

모든 공개 클래스와 구조체는 클래스 주석을 담고 있어야 한다. 작성 요령은 주석 작성 요령과 동일하다.

#####  Command 정의 순서

| No.  | 명령                                           | 비고 |
| ---- | ---------------------------------------------- | ---- |
| 1    | @details {detailed description}                |      |
| 2    | @tparam <template-paramter-name> {description} |      |

##### 작성 예시

```cpp
/// @details 
/// StringTokenizer는 wchar와 char를 모두 지원하며, 최적화된 성능을 제공합니다. 또한 stl 친화적인 사용을 위해 std::vector<std::string_view> 를
/// 상속하여 데이터 접근 편의성을 높였습니다.StringTokenizer 사용을 위해 가장 먼저 Delimiter를 설정하고, 토큰링할 문자열을 전달하여 토큰링을 실행
/// 합니다. 토큰링 실행이 완료되었다면 결과에 접근하기 위해 for-range, iterator, operator[], at() 메서드 등을 이용 할 수 있습니다.
/// @tparam CharType char와 wchar를 지원합니다. 토큰링할 문자열이 와이드 캐릭터 일 경우 wchar를 지정하고, 그렇지 않을 경우 char를 지정합니다.
/// @warning StringTokenizer의 CharType은 char 또는 wchar만을 지원합니다. 다른 타입이 입력될 경우 컴파일 에러가 발생합니다.
template <typename CharType>
class StringTokenizer : public std::vector<std::basic_string_view<CharType>> {
	...snip...  
};
```



#### 함수(or 메서드) 주석

전역 함수나 클래스의 공개 메서드에는 무조건 함수(or 메서드)가 무슨 일을 하는지를 설명하는 주석이 있어야 한다. 작성 요령은 주석 작성 요령과 동일하다.

##### Command 정의 순서

| No1. | 명령                                                 | 비고                                                         |
| ---- | ---------------------------------------------------- | ------------------------------------------------------------ |
| 1    | @details {detailed description}                      |                                                              |
| 2    | @code {.language-id}                                 | 현재 사용되는 프로젝트가 C++이므로<br />@code {.cpp}를 사용한다. |
| 2    | @endcode                                             |                                                              |
| 3    | @tparam <template-paramter-name> {description}       | 템플릿 메서드일 경우에만 사용된다.                           |
| 4    | @param[dir] <parameter-name> {parameter description} | 파라메터가 존재할 경우에만 사용된다.                         |
| 5    | @return {description of the return value}            | 반환 값이 있을 경우에만 사용된다.                            |
| 6    | @throw {exception description}                       |                                                              |

##### 작성 예시

```cpp
/// @details 문자열을 받아 문자열을 토큰링하고, 토큰링 결과를 std::vector<std::basic_string_view<CharType>> 형태로 저장합니다. 그리고 모든 
/// 토큰링 작업이 정상적으로 마무리 되었다면 엘리먼트 갯수를 반환합니다. 
/// @param[in] body 토큰링하기 위한 문자열 입니다. 
/// @param[in] reserve_size 결과를 담기 위한 vector의 메모리를 예약합니다. 
/// @return 토큰링된 결과 원소의 갯수를 반환합니다. 
/// @note 큰 문자열을 토큰링하는 경우 실행 시점에 예상되는 메모리를 미리 예약하여 메모리 재햘당 이슈를 예방해야 합니다. 
int32_t Execute(const std::basic_string_view<CharType> body, const size_t& reserve_size = kDefaultReservedSize) {
	...snip...
    return static_cast<int32_t>(_super_t::size())); // 토큰링 결과 갯수를 반환합니다.
}
```



#### 변수 및 Enum Class 필드 주석

공개된 변수의 용도를 간략하게 설명하기 위해 사용되며, 선언된 이름이 명확할 경우 제외 가능하다. 또한 변수 주석은 같은 라인에 작성해야 하며, 주석 작성 방식은 비고란과 작성 예시를 참고한다.

##### Command 정의 순서

| No.  | 명령                       | 비고                                                         |
| ---- | -------------------------- | ------------------------------------------------------------ |
| 1    | @brief {brief description} | 실 사용시 다른 주석과 다르게 `/// @brief`가 아니라 <br />`///< brief`를 사용해야 합니다. |

##### 작성 예시

```cpp
static constexpr int32_t kDefaultReservedSize = 100; ///< brief 토큰링 실행 시 결과 저장에 사용될 기본 메모리 예약 사이즈 입니다.
```



#### Enum Class 주석

Enum Class는 행동을 갖지 않기 때문에 Enum Class 선언과 원소들의 간략한 설명을 추가합니다. Enum Class의 사용된 이름만으로 설명을 대체할 수 있다면 제외 가능합니다.

##### Command 정의 순서

| No.  | 명령                            | 비고 |
| ---- | ------------------------------- | ---- |
| 1    | @details {detailed description} |      |

##### 작성 예시

```cpp
/// @details Doxygen 코드 블럭(@code {.languageid}/@endcode) 사용시 코드블럭 시작 시 스타일 지정에 사용됩니다.
enum class DoxygenLanguageId {
	kCpp = 1, ///< Brief C++ 스타일
    kJava = 2, ///< Brief Java 스타일
    kCShap = 3, ///< Brief C# 스타일
    kGo = 4, ///< Brief Go 스타일
    ...snip...
};
```



## 전처리 지시자

 전처리기 지시자 시작 부분에 사용되는 `#` 기호는 항상 그 줄의 처음에 있어야 한다. 또한 전처리 지시자가 중첩될 경우 들여쓰기하여 사용하며 이 때도 `#` 기호는 시작 부분에 위치해야 한다.

```cpp
#if defined(__GNUC__)
#   if __GNUC__ > 3
...
#   endif
#endif
```

전처리 지시자와 `#define`을 같이 사용할 경우 `#define`도 중첩 전처리 지시자와 동일하게 탭을 사용한다.

```cpp
#if defined(_MSC_VER)
#   define SPSG_VERION 0.0.1
#endif
```



## 헤더

 헤더 순서는 가독성을 높이고 숨겨진 종속성을 피하기 위해서 가장 첫 줄에 자신의 .h 파일을 include 하며 C 헤더, C++ 헤더, boost 헤더, 기타 라이브러리 헤더, 현재 프로젝트 헤더 순으로 한다.

- `Network.cpp` 헤더 정의

    ```cpp
    // 1. 해당 .cpp의 .h 파일
    #include "Network.h"
    
    // 2. C 라이브러리
    #include <stdio.h>
    
    // 3. C++ 라이브러리
    #include <iostream>
    #include <vector>
    #include <string>
    
    // 4. Boost 라이브러리
    #include <boost/noncopyable.hpp>
    #include <boost/asio.hpp>
    
    // 5. 기타 라이브러리
    #include <fmt.h>
    
    // 6. 현재 프로젝트의 .h 파일
    #include "Session.h"
    ```

미리 컴파일된 헤더는 라이브러리와 같이 개발 중 크게 변하지 않는 헤더들로 구성해야한다.
- `pch.h`
  
    ```cpp
    #if defined(_WIN32) || defined(_WIN64)
    #   define NOMINMAX
    #   define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
    #   include <Windows.h>
    #endif // end _WIN32 or _WIN64
    
    // 2. C 라이브러리
    #include <stdio.h>
    
    // 3. C++ 라이브러리
    #include <iostream>
    #include <vector>
    #include <string>
    
    // 4. Boost 라이브러리
    #include <boost/noncopyable.hpp>
    #include <boost/asio.hpp>
    
    // 5. 기타 라이브러리
    #include <fmt.h>
    ```

여러 프로젝트에서 미리 컴파일된 헤더에 공통으로 사용할 헤더를 모아 놓고 사용해도 좋다. 이때는 표준 라이브러리만 정의하는 것을 권장한다.
- `CommonHeaders.h`

    ```cpp
    #if defined(_WIN32) || defined(_WIN64)
    #   define NOMINMAX
    #   define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
    #   include <Windows.h>
    #endif // end _WIN32 or _WIN64
    
    // C 라이브러리
    #include <stdio.h>
    
    // C++ 라이브러리
    #include <iostream>
    #include <vector>
    #include <string>
    ```

내부 공통 헤더의 경우 `#include` 시 `<>`를 사용하며 자신의 프로젝트에 존재하는 헤더는 `""`를 사용하여 `#include` 한다.

```cpp
#include <SGSP/Utilitytime.h>
#include "Session.h"
...
```

<br/>

> #### include 시 주의사항
>
> namespace 영역 안에는 #include 를 금지한다. namespace 영역의 범위가 변경되어 버린다.
>
> ```cpp
> namespace foo {
> #include <map> // std::map 이 아니라 --> foo::std::map 이 됨...
> }
> ```
{: .block-danger }


<br/>

---

## 네임스페이스(namespace)

 라이브러리 간 이름 충돌을 예방하기 위해 `namespace`를 반드시 사용해야한다. `namespace` 이름은 모두 소문자로 작성하며 언더스코어를 이용하여 단어를 구분한다.

```cpp
namespace sgsp {
} // namespace sgsp
```

솔루션, 프로젝트, 디렉터리를 기반하여 작성하며, 중첩 `namespace`는 `::`로 구분한다. 예를 들어 `SGSP` 솔루션에 `Network` 프로젝트가 있고, `Network` 프로젝트에 `Detail`디렉토리가 있을 경우 다음과 같이 작성한다.

> `::`를 통해 namespace를 한 줄로 선언 할 수 있는 문법은 C++17 부터 제공되는 기능입니다.

```cpp
namespace sgsp::network::detail {
} // namespace sgsp::network::detail
```

중첩 `namespace`에서 영역이 겹치더라도 따로 분리하여 `namespace`를 정의 한다. 예를 들어 `namesapce sgsp`에 `namespace network`와 `namespace peer`가 존재할 경우 다음과 같이 작성한다.

```cpp
// 가이드에 따라 네임스페이스 영역이 겹치더라도 분리하여 작성
namespace sgsp::network {
    
} // namespace sgsp::network

namespace sgsp::peer {
    
} // namespace sgsp::peer

// 가이드를 준수하지 않았으므로 옳지 않다.
namespace sgsp {
namespace network {
} // namespace network

namespace peer {
} // namespace peer
} // namespace sgsp
```

위 규칙을 준수했을 경우 같은 네임스페이스 중복 선언이 필요한 상황이 존재할 수 있다. 다음 예제 코드를 보면 각자의 기능을 구현하기 위해 서로 참조하게 된다. 이 경우 현재 규칙을 따르게 된다면 boost::system 네임스페이스가 두 번 선언되는 이슈가 발생한다. 일단 해당 상황이 일반적이지는 않기 때문에 협의를 통해 위 정책을 따르기로하였으며, 작업 중 이와 유사한 문제로 인해 지속적으로 불편이 발생한다면 상황별 네임스페이스 선언 정책을 재논의하여 변경해야 한다.

```cpp
// 1. boost::system::detail 네임스페이스에서 사용하기 위한 메서드 선언
namespace boost::system {
template<> struct is_error_code_enum<sgsp::net::ErrorCode> : std::true_type {};

SGSP_ERROR_SYSTEM_CONSTEXPR inline boost::system::error_code make_error_code(sgsp::net::ErrorCode e) BOOST_NOEXCEPT;
SGSP_ERROR_SYSTEM_CONSTEXPR inline boost::system::error_condition make_error_condition(sgsp::net::ErrorCode e) BOOST_NOEXCEPT;
} // namespace boost::system

// 2. 위 선언을 사용하여 기능 정의
namespace boost::system::detail {
class excpetion_category : public boost::system::error_category {
public:
	// ... 중략 ...

private:
	std::string message_;
};

class custom_error_category : public boost::system::error_category
{
public:
	// ... 중략 ...
    
    // OPTIONAL: Allow generic error conditions to be compared to me
	boost::system::error_condition default_error_condition(int c) const noexcept override final {
		auto err = static_cast<sgsp::net::ErrorCode>(c);
		switch (err) {
			case sgsp::net::ErrorCode::kNotConnected: {
				return boost::system::make_error_condition(err); // sgsp::net::ErrorCode를 사용하는 make_error_condition 호출
			}

			default: {
				return boost::system::error_condition(c, *this);
			}
		}
	}
};

template<class T> struct BOOST_SYMBOL_VISIBLE custom_cat_holder {
	static constexpr custom_error_category instance{};
};

template<class T> constexpr custom_error_category custom_cat_holder<T>::instance;

constexpr boost::system::error_category const& custom_category() BOOST_NOEXCEPT {
	return boost::system::detail::custom_cat_holder<void>::instance;
}
} // namepsace boost::system::detail

// 3. 상위에 선언한 메서드 정의
namespace boost::system {
// exception에 대한 category는 호출 시 마다 생성한다.
SGSP_ERROR_SYSTEM_CONSTEXPR inline boost::system::error_code make_error_code(sgsp::net::ErrorCode e, const char* message) BOOST_NOEXCEPT {
	return boost::system::error_code(static_cast<int32_t>(e), boost::system::detail::excpetion_category(message));
}

SGSP_ERROR_SYSTEM_CONSTEXPR inline boost::system::error_code make_error_code(sgsp::net::ErrorCode e) BOOST_NOEXCEPT {
	return boost::system::error_code(static_cast<int32_t>(e), boost::system::detail::custom_category());
}

SGSP_ERROR_SYSTEM_CONSTEXPR inline boost::system::error_condition make_error_condition(sgsp::net::ErrorCode e) BOOST_NOEXCEPT {
	return boost::system::error_condition(static_cast<int32_t>(e), boost::system::detail::custom_category());
}
} // namespace boost::system
```

`namespace`의 여는 중괄호는 `namespace` 이름과 같은 라인에 위치하며 이름과 중괄호 사이에 space가 들어간다.

```cpp
// 정상
namespace sgsp {
} // namespace sgsp

// namesapce 이름과 여는 중괄호 사이에 공백이 없으므로 옳지 않다.
namespace sgsp{
} // namespace sgsp

// 여는 중괄호가 개행되었기 때문에 옳지 않다.
namespace sgsp
{
} // namespace sgsp
```

`namespace`를 닫는 중괄호에는 주석을 통해 `namespace`를 명시한다.

```cpp
namespace sgsp {
} // namespace sgsp
```

`namespace` 키워드 앞에 space 없이 작성한다.

```cpp
// 정상
namespace sgsp::network {
} // namespace sgsp::network

// network namespace에 tab이 존재하므로 옳지 않다.(폐기 예정)
namespace sgsp {
    namespace network {

    } // namespace network
} // namespace sgsp
```

전역으로 `using namespace`를 사용하지 않는다.

```cpp
// 헤더에 이와같이 namespace using을 사용하지 않는다. 
using namespace sgsp::network;
```



## 정수 타입

 stdint.h에 정의되어 있는 명확한 크기의 정수타입을 사용한다. 다만 `size_t`나 `time_t` 등과 같이 널리 사용되고 있는 타입은 사용 가능하다.

|기존 타입|stdint 타입|비고|
|:---|:---|:---|
|`char`|`char` or `int8_t`|charater를 표현 할 경우 `char`를 사용 그렇지 않고 부호없는 1byte를 표현할 경우 `int8_t` 사용|
|`unsigned char`|`uint8_t`||
|`short`|`int16_t`||
|`unsigned short`|`uint16_t`||
|`int`|`int32_t`||
|`unsigned int`|`uint32_t`||
|`long long`|`int64_t`||
|`unsigned long long`|`uint64_t`||
|`time_t`|`time_t`||
|`size_t`|`size_t`||



## 상수(Constant)

 상수는 접두사로 k를 사용하며 이름은 대문자로 시작하여 각 단어의 첫 글자를 대문자로 쓰고, 언더스코어는 사용하지 않는다.

```cpp
// C++11 이후 컴파일러에서는 상수 정의시 const 대신 constexpr을 사용합니다.
constexpr int32_t kZoneFrameMs = 100;
static constexpr int32_t kZoneManagerFrameMs = 50;

// C++11 이전
const int32_t kZoneFrameMs = 10;
static const int32_t kZoneManagerFrameMs = 50;
```

`class` 멤버에 정의된 `static const`의 경우 `MSVC`와 `GCC`에서의 컴파일 결과가 다릅니다. 다음은 class 멤버의 `static const`를 사용하는 간단한 예입니다. 해당 예제는 MSVC 컴파일러로 컴파일 할 경우 문제 없이 컴파일 되지만, GCC를 이용해 컴파일 할 경우에는 컴파일 에러가 발생합니다.

```cpp
class StaticMember {
public:
    static const int32_t kValue = 10;
};

int Foo(const int& n) {
   return n; 
}

int main() {
    // GCC 컴파일러로 컴파일 시 에러 발생(error: undefined reference to `StaticMember::kValue`)
    Foo(StaticMember::kValue); 
}
```

해당 문제를 해결하기 위해서는 C++17 전과 후로 처리가 나뉘게 됩니다. 일단 C++17 이전 해결 방법은 다음과 같습니다.

```cpp
class StaticMember {
public:
    static const int32_t kValue = 10;
};
const int32_t StaticMember::kValue;
```

다음으로 C++17 이후부터 가능한 해결 방법입니다.

```cpp
class StaticMember {
public:
    static constexpr int32_t kValue = 10;
    // or static inline int32_t kValue = 10;
};
```

결과적으로  C++17 이 지원되는 컴파일러를 사용한다면 상수를 정의 할때 constexpr 사용을 권장합니다. 이 외에도 constexpr을 사용해야하는 이유는 constexpr은 리터널 타입이 사용됐을 경우 컴파일 타임에 평가되어 상수화된다는 장점이 있습니다. conextexpr에 대한 자세한 내용은 [여기](https://en.cppreference.com/w/cpp/language/static)를 참고해주세요.



## 열거형(Enumeration)

 열거형 이름은 대문자로 시작하여 각 단어의 첫 글자를 대문자로 쓰고, 언더스코어는 사용하지 않는다.

```cpp
enum class ErrorCode {
};
```

열거자(Field)는 매크로와의 충돌을 피하기 위해 상수와 같은 이름 규칙을 사용한다.

```cpp
enum class ErrorCode {
    kOk = 0,
    kOutOfMemory = 1
};
```

범위 열거형을 사용하며 `enum`은 더 이상 사용하지 않는다.

```cpp
// 기존 enum을 사용할 경우 이름 규칙이 필요하며 지켜지지 않았을 경우 충돌 발생
// 2>D:\2.Workspace\Example\Example\tbb\main.cpp(231,2): error C2365: 'NONE': 재정의: 이전 정의는 '열거자'입니다.
// 2>D:\2.Workspace\Example\Example\tbb\main.cpp(226): message : 'NONE' 선언을 참조하십시오.
// 2>D:\2.Workspace\Example\Example\tbb\main.cpp(232,2): error C2365: 'IDEL': 재정의: 이전 정의는 '열거자'입니다.
// 2>D:\2.Workspace\Example\Example\tbb\main.cpp(227): message : 'IDEL' 선언을 참조하십시오.
enum EntityState {
    NONE = 0,
    IDEL = 1,
};

enum SessionState {
    NONE = 0,
    IDEL = 1
}

// 위와 같은 문제가 발생할 경우 이름을 고유하게 사용하였으니 enum class로 인해 그런 수고를 할 필요가 없어졌다.
enum class ErrorCode {
    kOk = 0,
    kOutOfMemory = 1
};
```



## 매크로

 특별한 경우가 아니라면 사용하지 않는다. 꼭 사용해야 할 경우 대문자와 언더스코어로만 이름을 짓는다.

매크로 사용 전에 `inline` 함수, `const` 변수, `enum class` 사용을 고려해야한다.

```cpp
#define DYAS_OF_WEEK 7
```



## 변수 및 배열 초기화

 변수 초기화 시 `=`, `()`, `{}`를 사용 할 수 있으나 우리는 `=` 을 사용한다. 전역/멤버/지역을 포함한 모든 변수는 선언과 동시에 초기화해야 한다. 포인터가 아닌 객체에 대한 초기화는 해당 객체 내에서 처리되어야 하기 때문에 별도로 초기화 하지 않아도 된다.

```cpp
class MyClass {
    ...
private:
    int32_t id_ = 10;
};

int32_t id = 10;
```

`{}` 를 사용 할 경우 initializer_list 생성자가 있는 타입에서 주의가 필요하다.

```cpp
// 100개의 0을 포함한 벡터
std::vector<int32_t> vec(100, 0); 

// 100, 0의 두 원소가 있는 벡터
std::vector<int32_t> vec{100, 0};
```

Pointer(`*`) 및 Reference(`&`) 타입 정의 시 타입과 기호 사이에 space가 존재해서는 안된다.

```cpp
int32_t value = 10;

// 정상
int32_t* pointer_value = &value;
int32_t& reference_value = value;

// 타입과 기호 사이에 space가 존재하므로 옳지 않다.
int32_t *pointer_value = &value;
int32_t &reference_value = value;

// 포인터와 레퍼런스 기호 양 옆에 space가 존재하므로 옳지 않다.
int32_t * pointer_value = &value;
int32_t & reference_value = value;
```

선언과 동시에 초기화를 기본으로 하기 때문에 한줄에 여러개의 변수를 선언할 수 없다. 그렇기 때문에 포인터(`*`) 및 레퍼런스(`&`)를 변수 앞에 붙일 일이 없다.

```cpp
// 정상
Ability* player_ability = GetAbility(EntityType::kPC); // or nullptr
Ability* npc_ability = GetAbility(EntityType::kNPC); // or nullptr

// 아래와 같은 선언은 즉시 초기화되지 않기 때문에 옳지 않다.
Ability* player_ability, *npc_ability;
player_ability = GetAbility(EntityType::kPC);
npc_ability =  = GetAbility(EntityType::kNPC);
```

`{}`사용 할 경우 `{}`앞뒤로 공백을 사용하지 않는다.

```cpp
// 정상
vector<int> x{1, 2, 3, 4};
vector<T> x{% raw %}{{}, {}, {}, {}}{% endraw %};
f(MyMap[{composite, key}]);
new int[3]{1, 2, 3};

// { } 안쪽에 공백이 들어가서 옳지 않다.
vector<int> x{ 1, 2, 3, 4 };
vector<T> x{ {}, {}, {}, {} };
f(MyMap[{ composite, key }]);
new int[3]{ 1, 2, 3 };

// { } 앞에 공백이 들어가서 옳지 않다.
Foo foo { bar };
Foo {};
vector<int> { 1, 2, 3 };
new int[3] { 1, 2, 3 };
```

배열 선언시 배열명과 `[]`사이에 공백을 두지 않는다.

```cpp
// 정상
int a[5];
int a[5][5];

// a 와 [5] 사이에 공백이 들어가서 옳지 않다.
int a [5];
int a [5][5];
```

비트 필드의 경우 기존 콜론에 대한 정책들과 같이 앞뒤에 공백을 넣는다.

```cpp
struct IpAddr {
	uint32_t addr4 : 8;
	uint32_t addr3 : 8;
	uint32_t addr2 : 8;
	uint32_t addr1 : 8;
};
```



## 타입 재정의

 타입 재정의는 `typedef` 대신 `using`을 사용하여 작성하는 것을 권장하며 타입 재정의 이름 규칙은 언더스코어로 시작하며 소문자를 사용하여 단어마다 언더스코어를 사용한다. 또한 접미사로 `_t`를 사용한다.

```cpp
// template 파라메터를 이용한 재정의(typedef에서는 해당 기능이 제공되지 않음.)
template <typename Element>
using _myvector_t = std::vector<Element>;

// map 재정의
using _property_map_t = std::map<int32_t, Property>;
```



## 함수

 함수 이름은 대문자로 시작하며 언더스코어 없이 단어마다 첫 글자로 대문자를 사용한다. 클래스 멤버 함수와 전역 함수 모두 같은 규칙을 따른다.

```cpp
// 멤버 함수 선언 예시
class MyClass {
public:
    int32_t SumAndGet(const int32_t& lvalue, const int32_t& rvalue) { 
        return lvalue + rvalue;
    }
};

// 함수 선언 예시
void TickCount() {
    // TODO: 내용 작성
}
```

함수 이름과 여는 소괄호 사이에는 space가 있어서는 안된다.

```cpp
// 정상
void TickCount();

// 함수 이름과 여는 소괄호 사이에 space가 존재하므로 옳지 않다.
void TickCount (); 
```

닫는 소괄호와 여는 중괄호는 항상 마지막 인자와 같은 줄에 작성해야 한다.

```cpp
// 함수 선언 예시
void TickCount() {
    // TODO: 내용 작성
}

// 닫는 소괄호와 여는 중괄호는 항상 마지막 인자와 같은 라인에 존재해야하며 개행 시 첫번째 인자부터 모든 인자를 개행하도록 한다.
void Initialize(
    const int32_t& id,
    const std::vector<int32_t>& data) {
}
```

소괄호 사이에는 space가 존재해서는 안된다.

```cpp
// 정상
void Update(const int32_t& delta, const std::string& extra);

// 소괄호 사이에 space가 존재하므로 옳지 않다.
void Update( const int32_t& delta, const std::string& extra );  
void Update( const int32_t& delta, const std::string& extra);   
void Update(const int32_t& delta, const std::string& extra );   
```

레퍼런스(`&`)로 전달되는 모든 인자는 `const`로 수식되어야한다. 다만 `nullptr`를 전달해야 하는 경우는 Pointer(`*`)를 사용한다. 파라메터의 경우 레퍼런스 또는 포인터로 넘길 경우 타입에 따라 `nullptr` 체크가 꼭 필요하다.

```cpp
// 레퍼런스 전달 예시
void Func(const MyCalss& my_class);

// 포인터 전달 예시
void Func(const MyClass* my_calss);
```

함수 인수 중 사용되지 않는 경우 인수명을 제거하지 않고 주석 처리한다.

```cpp
void OnEvent(const boost::system::error_code& /*error_code*/) {
    ...
}
```

함수 선언 시 글자수가 너무 많을 경우 파라메터를 개행한다. 개행된 파라메터는 탭(4space) 들여쓰기 한다. 개행이 필요한 경우, 한 라인에는 하나의 파라메터만 넣도록 한다.

```cpp
// 한줄에 쓰기에는 글자수가 너무 많은 멤버 함수
void MyClass::Initialize(const int32_t& id, const IConfiguration* configuration, const IListener* listener, const Logging* logging) {
    ...
}

// 파라메터 개행
void MyClass::Initialize(
    const int32_t& id, 
    const IConfiguration* configuration, 
    const IListener* listener, 
    const Logging* logging) {
    ...
}
```

함수 사용 시 파라메터가 많아 가독성이 떨어질 경우 개행하며 개행된 파라메터는 탭(4space)로 들여쓰게한다. 이때 닫는 소괄호는 마지막 인자와 같은 줄이 위치한다. 함수 선언 시와 동일하게 개행이 필요한 경우, 한 라인에는 하나의 파라메터만 넣도록 한다.

```cpp
Initialize(
    id,
    configuration,
    listener,
    logging);
```

> **Clang-format 주의사항**
>
> 함수 선언과 함수 호출 시 모두 파라메터 개행을 하는 경우에는 반드시 첫 번째 파라메터부터 개행해야 한다. 첫 번째 파라메터가 개행되어있지 않으면 뒤에 다른 파라메터들을 모두 개행 했더라도 clang-format 동작에 의해서 한줄로 변경 된다.
>
> ```cpp
> // 함수 선언 이렇게 되어있으면,
> void Initialize(const int32_t& id
> 	, const IConfiguration* configuration
> 	, const IListener* listener
> 	, const Logging* logging) {
> }
> 
> // 이렇게 한줄로 수정 된다.
> void Initialize(const int32_t& id, const IConfiguration* configuration, const IListener* listener, const Logging* logging) {
> }
> 
> // 함수 호출도,
> Initialize(id,
> 	configuration,
> 	listener,
> 	logging);
> 
> // 마찬가지로 한줄로 수정 된다.
> Initialize(id, configuration, listener, logging);
> ```



함수 사용 시 파라메터에 람다가 존재 하는 경우, 무조건 개행한다.

```cpp
// 정상
sgsp::thread::ConditionalWait::Run(
    [&count] {
        return 2 == ++count;
    },
    std::chrono::milliseconds(1));

// 람다 파라메터가 존재하는데 개행하지 않아 옳지 않다.
sgsp::thread::ConditionalWait::Run([&count] {
	return 2 == ++count;
}, std::chrono::milliseconds(1));
```

> **Clang-format 주의사항**
>
> 람다가 첫 번째 파라메터로 있는 경우, clang-format의 동작이 이상해지는 상황이 발생한다. 이를 회피하기 위해 람다가 파라메터에 포함되는 경우, 무조건 개행하도록 한다.
>
> ```cpp
> // 위에 개행하지 않은 예제를 포맷팅 하면 뒤의 인자가 이상하게 정렬되는 것을 볼 수 있다.
> sgsp::thread::ConditionalWait::Run([&count] {
> 	return 2 == ++count;
> },
> 								   std::chrono::milliseconds(1));
> ```



인라인 함수는 컴파일러가 함수를 인라인화하여 더 효율적인 오브젝트 코드를 생성 할수 있다. 클래스 내부에 구현된 메서드의 경우 컴파일 단계에서 컴파일러에 의해 인라인화 되기 때문에 별도 키워드를 넣지 않도록 한다.

```cpp
class MyClass {
public:
    int32_t GetValue() const {
        return value_;
    }

    void SetValue(const int32_t& value) {
        value_ = value;
    }

private:
    int32_t value_ = 0;
};
```

리턴타입이 길어져서 개행이 필요하다고 판단한 경우, 개행 후에 함수명은 들여쓰기 하지 않는다.

```cpp
// 리턴타입이 너무 길다고 판단.
std::unique_ptr<sgsp::interfaces::NetworkStubInterface> Create(const sgsp::interfaces::PacketSerializationType& type);

// 개행
std::unique_ptr<sgsp::interfaces::NetworkStubInterface>
Create(const sgsp::interfaces::PacketSerializationType& type);
```



## if 문

 `if` 키워드와 여는 소괄호 사이에 스페이스를 사용한다.

```cpp
// 정상
if (cond) {
}

// if 키워드와 여는 소괄호 사이에 스페이스가 존재하지 않으므로 옳지 않다.
if(cond) {
}
```

소괄호 사이 스페이스를 사용하지 않는다.

```cpp
// 정상
if (cond) {
}

// 소괄호 사이에 space가 존재하므로 옳지 않다.
if ( cond ) {
}

if ( cond) {
}

if (cond ) {
}
```

여는 소괄호와 첫 인자는 if와 같은 줄에 위치한다.

```cpp
// 정상
if (cond) {
}

// 여는 소괄호가 개행되었으므로 옳지 않다.
if
(cond) {

}
```

닫는 소괄호는 마지막 조건과 같은 줄에 위치한다.

```cpp
// 정상
if (cond1
	&& cond2) {
}

// 닫는 소괄호가 마지막 인자와 다른 라인에 존재하므로 옳지 않다.
if (cond1 
	&& cond2
	) {
}
```

여는 중괄호는 닫는 소괄호와 같은 줄에 위치해야 하며 닫는 소괄호와 여는 중괄호 사이에는 space가 있어야한다.

```cpp
// 정상
if (cond1) {
}

// 닫는 소괄호와 여는 중괄호 사이에 space가 없어 옳지 않다.
if (cond1){
}

// 여는 중괄호가 닫는 소괄호와 다른 줄에 있으므로 옳지 않다.
if (cond) 
{
}
```

`else if`와 `else`는 닫는 중괄호에서 한 줄 개행하여 사용한다.

```cpp
// else if와 else는 닫는 소괄호와 다른 줄에 위치해야 한다.
if (cond1) {

}
else if (cond2) {

}
else {

}
```
`else`를 사용하지 않는 짧은 조건문의 경우도 중괄호를 사용하며 개행한다.

```cpp
// 정상
if (cond1) {
    continue;
}

// 해당 규칙이 지켜지지 않았으므로 옳지 않다.
// 중괄호를 사용하였으나 개행이 없다.
if (cond1) { continue; }    

// 중괄호 및 개행이 없다.
if (cond1) continue;     

// 중괄호가 없다.
if (cond1)                  
    continue;
```

rvalue 또는 contant 변수를 왼쪽에 위치시켜 비교 연산자 오타로 인한 문제를 예방한다.

```cpp
// 정상
if (true == cond1) {
}

if (ErrorCode::kOk != cond1) {
}

// 오타로 인해 문제 발생
if (cond1 = true) {
}

if (cond1 = ErrorCode::kOk) {
}
```

조건이 길어질 경우 조건을 개행하며 AND 또는 OR 연산자와 같이 개행한다.

```cpp
if (true == cond1
	&& true == cond2
	&& true == cond3
	&& true == cond4) {

}
```

init-statement 사용 시 가독성을 해치는 코드는 사용해서는 안된다. 내부 논의 결과 init-statement의 경우 가독성을 위해 메서드 및 람다를 사용하지 않기로 결정했다. (C++17 이상)

```cpp
// 짧은 메서드를 이용해 player의 nullptr을 체크하는 용도는 좋다
if (auto player = GetPlayer(usn)) {
    player->Update(delta);
}

// 람다 사용으로 가독성을 해치는 상황으로 옳지 않다.
if (auto result = [this]() {
    if (true == IsExist()) {
        return false;
    }

    ... 생략

    return true;
}(); true == result) {
    ...
}
```

`if`문 내에서 함수를 사용해서 라인이 길어지는 경우, 리턴값을 받은 후 확인 하는 방향을 권장한다.

```cpp
// 함수의 인자가 많아서 길어진 조건문
if (false == session_manager_->Create(io_context_, listener_, logging_, monitor_, configuration_, MakeNetworkStub(), session)) {
    ...생략
}

// 리턴값을 받아서 확인
bool rtn = session_manager_->Create(
    io_context_,
    listener_,
    logging_,
    monitor_,
    configuration_,
    MakeNetworkStub(),
    session);
if (false == rtn) {
    ... 생략
}
```

> **Clang-format 주의사항**
>
> `if`문 내에서 호출하는 함수의 파라메터들을 개행 하더라도 clang-format에서 포맷팅 하면 모두 한줄로 땡겨진다.



## 삼항연산자

한줄로 표현 가능한 간단한 구문에서만 사용한다. 표현이 길어지거나 삼항연산자를 중첩해서 처리해야 할 경우 `if`문을 사용한다.

`?`와 `:`앞뒤로 공백을 넣는다.

```cpp
// 정상
a > b ? a : b;

// ? 앞뒤에 공백이 없어서 옳지 않다.
a > b? a : b;
a > b ?a : b;

// : 앞뒤에 공백이 없어서 옳지 않다.
a > b ? a: b;
a > b ? a :b;

// 삼항연산자를 중첩사용해서 옳지 않다.
max = a > b
    ? c > a ? c : a
    : c > b ? c : b;
```

삼항 연산자 사용하는데 개행이 필요한 경우, `?`, `:` 이전에 개행하여 앞에 배치한다.

```cpp
// 정상
next_cur_data_ = next_cur_data_ == NetworkTestEnviroment::kSimplePakcet
    ? NetworkTestEnviroment::kLongPakcet
    : NetworkTestEnviroment::kSimplePakcet;

// ?와 :이 앞에 배치되지 않아서 옳지 않다.
next_cur_data_ = next_cur_data_ == NetworkTestEnviroment::kSimplePakcet ?
    NetworkTestEnviroment::kLongPakcet :
    NetworkTestEnviroment::kSimplePakcet;
```



## for, while 문

 `for`, `while` 키워드와 여는 소괄호 사이에 space를 사용하며 소괄호 사이에는 space가 존재하지 않는다.

[for 문]

```cpp
// 정상
for (auto i = 0; i < 10; ++i)

// for 키워드와 여는 소괄호 사이에 space가 존재하지 않으므로 옳지 않다.
for(auto i = 0; i < 10; ++i)

// 여는 소괄호와 닫는 소괄호 사이에 space이 존재하므로 옳지 않다.
for ( auto i = 0; i < 10; ++i )
for ( auto i = 0; i < 10; ++i)
for (auto i = 0; i < 10; ++i )
```

[while 문]

```cpp
// 정상
while (10 > count)

// while 키워드와 여는 소괄호 사이에 space가 존재하지 않으므로 옳지 않다.
while(10 > count)

// 여는 소괄호와 닫는 소괄호 사이에 space가 존재하므로 옳지 않다.
while( 10 > count )
while( 10 > count)
while(10 > count )
```

여는 중괄호는 닫는 소괄호와 같은 줄에 위치한다.

```cpp
// 정상
for (auto i = 0; i < 10; ++i) {
}

while (10 > count) {
}

// 여는 중괄호가 개행되었기 때문에 옳지 않다.
for (auto i = 0; i < 10; ++i) 
{
}

while (10 > count) 
{
}
```

`for` 문의 경우 세미콜론 후 스페이스를 사용한다.

```cpp
// 정상
for (auto i = 0; i < 10; ++i)

// 세미콘론 뒤에 공백이 없으므로 옳지 않다.
for (auto i = 0;i < 10;++i)
```

대입 연산자 및 비교 연산자 사이에 공백을 사용한다.

```cpp
// 정상
for (auto i = 0; i < 10; ++i)

while (10 > count)

// 연산자들 사이에 공백이 없으므로 옳지 않다.
for (auto i=0; i<10; ++i)

while (10>count)
```

비어있는 루프도 경우 중괄호를 사용하여 명확하게 한다.

```cpp
for (auto i = 0; i < 10; ++i) {
}

while (cond1) {
}
```

범위 `for`사용시 `:` 앞뒤에 공백을 사용한다.

```cpp
for (auto i : container) {
}
```



## do/while 문

 여는 중괄호는 `do`와 같은 줄에 위치하며 `while` 키워드는 닫는 중괄호와 같은 줄에 위치 후 사이에 스페이스를 사용한다.

```cpp
// 정상
do {

} while ();

// do 키워드와 여는 중괄호 사이에 space가 없으므로 옳지 않다.
do{

} while ();

// 여는 중괄호가 개행되었으므로 옳지 않다.
do
{

} while ();

// while 키워드와 닫는 중괄호가 같은 줄에 위치하지 않았으므로 옳지 않다.
do {

}
while ();

// whild 키워드와 닫는 중괄호, 여는 소괄호 사이에 space가 없으므로 옳지 않다.
do {
    
}while();

do {
    
}while ();

do {
    
} while();
```

소괄호 사이에는 space를 사용하지 않는다.

```cpp
// 정상
do {

} while (true == cond);

// 소괄호 사이에 space가 존재하므로 옳지 않다.
do {

} while ( true == cond );
```



## switch 문

 `switch` 키워드와 여는 소괄호 사이에는 space를 사용하며 여는 소괄호와 닫는 소괄호 사이에는 스페이스를 사용하지 않는다.

```cpp
// 정상
switch (cond) {
}

// space가 없으므로 옳지 않다.
switch(cond){
}
```

`switch` 문 여는 중괄호는 닫는 소괄호와 같은 줄에 위치하며 스페이스를 사용한다.

```cpp
// 정상
switch (cond) {
}

// 공백이 없으므로 옳지 않다.
switch (cond){
}

// 여는 중괄화가 닫는 소괄호와 다른 줄에 위치하므로 옳지 않다.
switch (cond) 
{
}
```

블록마다 중괄호를 사용하며 여는 중괄호는 `case` 문과 같은 줄에 위치한다. 이때 콜론과 여는 중괄호 사이에는 space를 사용한다. `case`블록은 `switch`블록 보다 한단계 들여쓰기 한다.

```cpp
switch (cond) {
    case 1: {
        break;
    }

    default: {
        break;
    }
}
```



## try/catch 문

`try`, `catch` 키워드 이후에는 공백을 사용하며, 중괄호는 같은 줄에 위치한다. `catch`문은 `else`문과 동일하게 중괄호 이후에 개행한다.

```cpp
// 정상
try {
}
catch (...) {
}

// 중괄호가 같은 줄에 위치하지 않아서 옳지 않다.
try
{
}
catch (...)
{
}

// try 키워드 이후에 공백이 없고, catch문의 중괄호 앞에 공백이 없어서 옳지 않다.
try{
}
catch (...){
}

// catch문 앞에서 개행하지 않아서 옳지 않다.
try {
} catch (...) {
}
```



## 구조체

 구조체 이름은 대문자로 시작하며 언더스코어 없이 단어마다 첫 글자로 대문자를 사용한다.

```cpp
// 정상
struct MyData {
};

// 언더 스코어를 사용하였기 때문에 옳지 않다.
struct MyData_Ability {
};
```

데이터의 묶음으로 함수를 가지지 않으며 클래스와 다르게 멤버 변수에 접미사로 언더스코어를 사용하지 않는다. 또한 접근 제한자도 사용하지 않으며 만일 함수 및 접근 제한자 등이 필요한 경우는 `class`를 사용해야 한다.

※ TODO: struct에 memset이나 memcpy 사용을 위해 POD 타입만 사용하자는 의견이 있음. 고민 필요.

```cpp
// 정상
struct MyData {
    int32_t id;
    std::string name;
    std::vector<Property> property;
};
```

예외 적인 상황으로 STL과의 일관성을 지키기 위해서 functor와 trait에 대해서는 class 대신 struct를 사용 가능하다.

```cpp
template <class _Ty = void>
struct less {
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef _Ty _FIRST_ARGUMENT_TYPE_NAME;
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef _Ty _SECOND_ARGUMENT_TYPE_NAME;
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef bool _RESULT_TYPE_NAME;

    _NODISCARD constexpr bool operator()(const _Ty& _Left, const _Ty& _Right) const {
        return _Left < _Right;
    }
};
```



## 인터페이스

 인터페이스 이름은 대문자로 시작하며 언더스코어 없이 단어마다 첫 글자로 대문자를 사용하며 접미사로 `Interface`를 사용한다.

```cpp
class RunnableInterface {
};
```

인터페이스는 순수 가상함수로 구성된 클래스를 의미하며 정적이 아닌 데이터 멤버를 가질 수 없다.

```cpp
// 정상
class RunnableInterface {
public:
    static const int32_t kTimeout = 10;

    virtual bool Run() = 0;
};

// 멤버 변수 및 일반 함수가 포함되어 있기 때문에 옳지 않다.
class RunnableInterface {
public:
    int32_t GetId() const {
        return id_;
    }

    const std::string& GetName() const { 
        return name_;
    }

    virtual bool Run() = 0;

private:
    int32_t id_ = 0;
    std::string name_;
};
```

인터페이스는 기본적으로 생성자를 선언하지 않으며 생성자 선언이 필요한 경우 기본 생성자를 선언하며 `protected`여야 한다. 또한 기본적으로 부모 클래스로 사용되기 때문에 virtual 소멸자를 가진다.

```cpp
class RunnableInterface {
public:
    virtual ~RunnableInterface() = default;
    virtual bool Run() = 0;

protected:
    IRunnable() = default;
};
```



## NonCopyable과 NonMoveable 타입

클래스 작성 시 이동과 복사를 명확히 해줘야 하는 경우가 있습니다. 기능을 제한해야 하는 경우 다음의 클래스를 상속하여 문제를 해결합니다.

| 클래스 이름               | 설명                    |
| ------------------------- | ----------------------- |
| NonCopyable               | 복사 불가능, 이동 가능  |
| NonMoveable               | 복사 가능, 이동 불가능  |
| NonCopyableAndNonMoveable | 이동과 복사 모두 불가능 |



## Rule Of Zero, Rule Of Three, Rule Of Five

### Rule Of Zero

소멸자, 복사 생성자, 복사 대입 연산자, 이동 생성자, 이동 대입 연사자를 재정의 하지 않도록 설계하는 것을 의미한다. 기본적으로 Rule Of Zero를 권장하며 리소스를 직접 관리해야할 경우 stl 자료구조나 스마트 포인터 사용을 우선 고민해야 합니다.

### Rule Of Three

소멸자, 복사 생성자, 복사 대입 연산자 중 하나를 정의했다면 나머지도 재정의 후 알맞은 처리를 해주어야 한다. 예를 들어 아래와 같이 raw pointer 를 가지는 객체가 있을 경우 우리는 일반적으로 객체가 소멸 시점에 리소스도 같이 소멸될 수 있도록 소멸자를 정의 후 해당 리소스를 해제하는 코드를 작성하게 됩니다.

```cpp
class RuleOfThree {
public:
    RuleOfThree() 
        : pointer_(new char[15]) {
    }

    // 리소스를 반환하기 위해 소멸자 정의
    ~RuleOfThree() {
        if (nullptr != pointer_) {
            delete[] pointer_;
        }
    }

private:
    char* pointer_ = nullptr;
};
```

이때 다음과 같이 `RuleOfThree` 객체가 복사되는 경우를 생각해보겠습니다.

```cpp
int main() {
    RuleOfThree rule_of_three;
    {
        auto copy_object = rule_of_three;
    }

    return 0;
}
```

만일 위와 같이 사용됐다면 `copy_object`와 `rule_of_three` 객체는 같은 `pointer_`의 주소를 바라보게 됩니다. 그렇기 때문에 `copy_object`가 스코프를 벗어날 경우 소멸자가 호출되면서 해당 리소스가 해제 됩니다. 이런 상황에 대응하기 위해 복사 생성자와 복사 대입 연사자를 재정의 하여 문제가 발생하지 않도록 다음과 같이 코드를 작성해야합니다.

```cpp
class RuleOfThree {
public:
    RuleOfThree() 
        : pointer_(new char[15]) {
    }

    // 깊은 복사 정의
    RuleOfThree(const RuleOfThree& other) {
        auto len = strlen(other.pointer_);
        pointer_ = new char[len];
        memcpy(pointer_, other.pointer_, len);
    }

    ~RuleOfThree() {
        if (nullptr != pointer_) {
            delete[] pointer_;
            pointer_ = nullptr;
        }
    }
    
	// 깊은 복사 정의
    RuleOfThree& operator=(const RuleOfThree& other) {
        auto len = strlen(other.pointer_);
        pointer_ = new char[len];
        memcpy(pointer_, other.pointer_, len);
        return *this;
    }

private:
    char* pointer_ = nullptr;
};
```

또는 `RuleOfThree` 객체의 복사가 되지 않도록 `NonCopyable`를 상속할 수도 있습니다.

```cpp
class RuleOfThree : private sgsp::NonCopyable {
public:
    RuleOfThree() 
        : pointer_(new char[15]) {
    }

    // 리소스를 반환하기 위해 소멸자 정의
    ~RuleOfThree() {
        if (nullptr != pointer_) {
            delete[] pointer_;
        }
    }

private:
    char* pointer_ = nullptr;
};
```

### RuleOfFive

`RuleOfThree`에 추가적으로 이동 생성자와 이동 대입 연사자를 포함합니다. 결국 소멸자, 복사 생성자, 이동 생성자, 복사 대입 연산자, 이동 대입 연산자 중 한가지를 재정의 했다면 다른 동작들도 모두 알맞게 재정의하여 기능을 작성해야 한다 입니다. `RuleOfThree`의 기능을 이동 생성자와 이동 대입 연산자를 정의하여 다시 작성해보겠습니다. (만일 이동 생성자 기능을 제거하고 싶을 경우 delete 키워드를 통해 직접 제거하거나 `NonMoveable`을 상속하여 처리 할 수 있습니다.)

```cpp
class RuleOfFive {
public:
    RuleOfFive() 
        : pointer_(new char[15]) {
    }

    RuleOfFive(const RuleOfFive& other) {
        auto len = strlen(other.pointer_);
        pointer_ = new char[len];
        memcpy(pointer_, other.pointer_, len);
    }

    RuleOfFive(RuleOfFive&& other) noexcept
        : pointer_(std::exchange(other.pointer_, nullptr)) {

    }

    ~RuleOfFive() {
        if (nullptr != pointer_) {
            delete[] pointer_;
            pointer_ = nullptr;
        }
    }

    RuleOfFive& operator=(const RuleOfFive& other) {
        auto len = strlen(other.pointer_);
        pointer_ = new char[len];
        memcpy(pointer_, other.pointer_, len);
        return *this;
    }

    RuleOfFive& operator=(RuleOfFive&& other) noexcept {
        std::swap(pointer_, other.pointer_);
        return *this;
    }

private:
    char* pointer_ = nullptr;
};
```



## 클래스

 클래스 이름은 대문자로 시작하며 언더스코어 없이 단어 마다 첫 글자로 대문자를 사용한다.

```cpp
// 정상
class EventController {
};

// 언더스코어를 사용했기 때문에 옳지 않다.
class EventController_ZoneEvent {
};

// 소문자로 시작했으므로 옳지 않다.
class eventController {
};
```

접근 제한자는 `public`, `protected`, `private` 순으로 정의한다. 접근 제한자는 한번만 선언한다. 만일 특정 접근 제한자가 사용되지 않을 경우 생략 가능하다.

```cpp
// 순서와 접근제한자에 대한 중복 선언이 없으므로 정상이다.
class MyClass {
public:

protected:

private:
};

// protected와 private이 사용되지 않아 생략됐다.
class MyClass {
public:
};

// 접근 제한자가 중복되어 선언되었으므로 옳지 않다.
class MyClass {
public:
...
public:     // <-- 중복 선언
...

private:
...

private:    // <-- 중복 선언
}
```

멤버 변수는 소문자를 사용하여 단어 마다 언더스코어를 사용한다. 또한 접미사로 언더스코어를 사용한다. 멤버 변수의 경우는 기본 `private` 으로 접근을 제한하며 Getter와 Setter를 이용하여 접근하도록 한다. 또한 선언과 동시에 초기화해야 한다.

```cpp
class MyClass {
public:
    // Getter
    int32_t GetThreadCount() const {
        return thread_count_;
    }

    // Setter
    void SetThreadCount(const int32_t& thread_count) {
        thread_count_ = thread_count;
    }

private:
    // 선언과 동시에 1로 초기화
    int32_t thread_count_ = 1;

    // 선언과 동시에 nullptr로 초기화(메모리 할당이 필요하다면 여기서 처리 또는 Init 메서드에서 처리)
    Property* property_ = nullptr;
};
```

각 접근제한자를 기준으로 선언은 보통 아래와 같은 순서여야 한다.
- 타입 재정의
- Enum
- 상수 (`static const` or `static constexpr` 데이터 멤버)
- 생성자
- 소멸자
- 정적 메서드
- Getter/Setter 메서드
- 일반 메서드
- 데이터 멤버

```cpp
class MyClass {
public:
    // 타입 재정의
    using _property_map_t = std::map<std::string, std::string>;

    // 열거형
    enum class ObjectType {
        kNone = 0,
        kType1 = 1,
        kType2 = 2
    };

    // 상수
    static constexpr int32_t kUpdateInterval = 10;

    // 생성자 소멸자
    MyClass() = default;
    ~MyClass() = default;

    // 정적 메서드
    static bool CreateObject(const ObjectType& object_type);

    // Getter/Setter 메서드
	int32_t GetValue() const {
        return value_;
    }
    
    void SetValue(const int32_t& value) {
        value_ = value;
    }

    // 일반 메서드
    void PlusValue(const int32_t& value) {
        value_ += value;
    }

private:
    // SetValue는 비공개 함수
    void SetValue(const int32_t& value) {
        value_ = value;
    }

    void Print() {
        std::cout << "value:" << value_ << std::endl;
    }

    // 데이터 멤버
    int32_t value_;
};
```

복사 생성자 및 initialzier_list를 가진 생성자를 제외한 인수가 하나인 생성자에는 반드시 `explicit` 키워드를 사용하여 암시적 변환을 막아야한다.

[생성자의 암시적 변환]

```cpp
class MyClass {
public:
	MyClass(std::string str) 
		: str_(str) {
	}

	MyClass(const char* str) 
		: str_(str) {
	}

	void Print() {
		std::cout << str_ << std::endl;
	}

private:
	std::string str_;
};

void Print(std::string str) {
	std::cout << __FUNCTION__ << std::endl;
}

void Print(MyClass myclass) {
	myclass.Print();
}

void main(int argc, char** argv) {
    //1>D:\2.Workspace\Example\Example\tbb\main.cpp(216,13): error C2668: 'Print': 오버로드된 함수에 대한 호출이 모호합니다.
    //1>D:\2.Workspace\Example\Example\tbb\main.cpp(210,6): message : 'void Print(MyClass)'일 수 있습니다.
    //1>D:\2.Workspace\Example\Example\tbb\main.cpp(206,6): message : 또는       'void Print(std::string)'
    //1>D:\2.Workspace\Example\Example\tbb\main.cpp(216,13): message : 인수 목록 '(const char [4])'을(를) 일치시키는 동안
	Print("abc");
}
```

[`explicit`를 사용하여 암시적 변환 제거]

```cpp
class MyClass {
public:
	explicit MyClass(std::string str) 
		: str_(str) {
	}

	explicit MyClass(const char* str) 
		: str_(str) {
	}

	void Print() {
		std::cout << str_ << std::endl;
	}

private:
	std::string str_;
};

void Print(std::string str) {
	std::cout << __FUNCTION__ << std::endl;
}

void Print(MyClass myclass) {
	myclass.Print();
}

void main(int argc, char** argv) {
    Print("abc");
}
```

복사 생성자 및 대입 연산자는 필요한 경우에만 작성하여 사용하고 기본적으로 쓸수 없게 해야한다. `boost::noncopyable`을 상속하여 복사 생성자 및 대입 연산자를 제거한다.

```cpp
#include <boost/noncopyable.hpp>

class MyClass : private boost::noncopyable {
public:

private:
};
```

생성자 멤버 초기화 리스트의 경우 개행을 통해 가독성을 높인다. 개행 시 콤마가 가장 앞으로 오며 콜론과 같은 라인에 위치 시킨다.

```cpp
class MyClass {
public:
    MyClass()
        : value1_(100)
        , value2_(200)
        , value3_(300)
        , value4_(400) {

    }

private:
    int32_t value1_;
    int32_t value2_;
    int32_t value3_;
    int32_t value4_;
}
```

클래스 상속 시에는 virtual 소멸자를 정의 하며, 메서드 오버라이드 시 virtual 키워드를 생략하고 override를 사용한다. `:`앞뒤에는 공백을 넣는다.

```cpp
class WorkerThread : public sgsp::interfaces::RunnableInterface {
public:
	virtual ~WorkerThread() = default;
    
    bool Run() override {
        return true;
    }
};
```

클래스 상속 목록은 가능한 한 줄에 배치하고, 줄이 길어질 경우, 콜론과 콤마 이후에 개행한다.

```cpp
class Foo :
    public Base1,
    public Base2 {
};
```

> **Clang-format 주의사항**
>
> 위 예제는 `BreakInheritanceList`옵션의 `AfterColon`타입이다. 다른 타입들이 15버전까지도 정상 처리 되지 않는 것으로 확인되어 이 옵션으로 스타일을 맞춘다. 기본적으로 예외상황에 한줄로 원복해주고, 콜론 이후 줄바뀐 상황에서만 공식 문서대로 동작한다.
>
> ```cpp
> // 한줄 기본 형식 포맷팅 후에 변화 없다.
> class BreakInheritanceList : public AfterColon, public Base {
> };
> 
> // 아래 같은 세 가지 케이스들은 한줄로 수정된다.
> class BreakInheritanceList
> : public AfterColon, public Base {
> };
> 
> class BreakInheritanceList : public AfterColon
> , public Base {
> };
> 
> class BreakInheritanceList : public AfterColon,
> public Base {
> };
> 
> // AfterColon 기본 형식
> class BreakInheritanceList :
> 	public AfterColon,
> 	public Base {
> };
> 
> // : 이후에 개행하면 AfterColon 기본 형식으로 수정된다.
> class BreakInheritanceList :
> public AfterColon, public Base {
> };
> ```
>



## 형변환

 형 변환은 C++ 캐스팅 연산자를 사용한다. 캐스팅은 안전성이 보장되지 않기 때문에 기본적으로 작성자가 판단하여 사용해야 한다.

> C 스타일 캐스팅은 C++ 스타일로 대체 가능하기 때문에 사용하지 않는다.
>
> ```cpp
> // C 스타일 캐스팅
> double result = (double)4 / 5;
> 
> // 모두 C++ 스타일 캐스팅으로 처리 가능
> double result = static_cast<double>(4) / 5;
> ```

### [`const_cast`]

레퍼런싱하는 Object의 cv-qualifier(constness, volatility)를 제거하는 캐스팅이다. 따라서 `const_cast`는 실제 존재하는 object가 별도로 있고 그것에 접근하는 방법을 변경한다. 일반적으로 사용될 일이 없다.

>cpprepeference : [https://en.cppreference.com/w/cpp/language/const_cast](https://en.cppreference.com/w/cpp/language/const_cast)

```cpp
#include <iostream>
 
struct type
{
    int i;
 
    type(): i(3) {}
 
    void f(int v) const
    {
        // this->i = v;                 // compile error: this is a pointer to const
        const_cast<type*>(this)->i = v; // OK as long as the type object isn't const
    }
};
 
int main() 
{
    int i = 3;                 // i is not declared const
    const int& rci = i; 
    const_cast<int&>(rci) = 4; // OK: modifies i
    std::cout << "i = " << i << '\n';
 
    type t; // if this was const type t, then t.f(4) would be undefined behavior
    t.f(4);
    std::cout << "type::i = " << t.i << '\n';
 
    const int j = 3; // j is declared const
    [[maybe_unused]]
    int* pj = const_cast<int*>(&j);
    // *pj = 4;      // undefined behavior
 
    [[maybe_unused]]
    void (type::* pmf)(int) const = &type::f; // pointer to member function
    // const_cast<void(type::*)(int)>(pmf);   // compile error: const_cast does
                                              // not work on function pointers
}
```

### [`static_cast`]

C++에서 가장 일반 적으로 사용되는 캐스팅이다. 실수형과 정수형, 정수형과 열거형 등의 기본 데이터 타입 간의 변환 및 상속관계의 클래스 계층 간의 업/다운 캐스팅, `void*`를 다른 타입의 포인터로 변환 시 주로 사용된다. `static_cast`는 컴파일 타임에 변환이 이루어 지기 때문에 실행 시점에 잘못된 캐스팅으로 문제가 발생 할 수 있으니 캐스팅 시 주의해야 한다.

>cpprepeference : [https://en.cppreference.com/w/cpp/language/static_cast](https://en.cppreference.com/w/cpp/language/static_cast)

```cpp
#include <vector>
#include <iostream>
 
struct B
{
    int m = 42;
    const char* hello() const
    {
        return "Hello world, this is B!\n";
    }
};
 
struct D : B
{
    const char* hello() const
    {
        return "Hello world, this is D!\n";
    }
};
 
enum class E { ONE = 1, TWO, THREE };
enum EU { ONE = 1, TWO, THREE };
 
int main()
{
    // 1. static downcast
    D d;
    B& br = d; // upcast via implicit conversion
    std::cout << "1) " << br.hello();
    D& another_d = static_cast<D&>(br); // downcast
    std::cout << "1) " << another_d.hello();
 
    // 2. lvalue to xvalue
    std::vector<int> v0{1,2,3};
    std::vector<int> v2 = static_cast<std::vector<int>&&>(v0);
    std::cout << "2) after move, v0.size() = " << v0.size() << '\n';
 
    // 3. initializing conversion
    int n = static_cast<int>(3.14);
    std::cout << "3) n = " << n << '\n';
    std::vector<int> v = static_cast<std::vector<int>>(10);
    std::cout << "3) v.size() = " << v.size() << '\n';
 
    // 4. discarded-value expression
    static_cast<void>(v2.size());
 
    // 5. inverse of implicit conversion
    void* nv = &n;
    int* ni = static_cast<int*>(nv);
    std::cout << "4) *ni = " << *ni << '\n';
 
    // 6. array-to-pointer followed by upcast
    D a[10];
    [[maybe_unused]]
    B* dp = static_cast<B*>(a);
 
    // 7. scoped enum to int
    E e = E::TWO;
    int two = static_cast<int>(e);
    std::cout << "7) " << two << '\n';
 
    // 8. int to enum, enum to another enum
    E e2 = static_cast<E>(two);
    [[maybe_unused]]
    EU eu = static_cast<EU>(e2);
 
    // 9. pointer to member upcast
    int D::*pm = &D::m;
    std::cout << "9) " << br.*static_cast<int B::*>(pm) << '\n';
 
    // 10. void* to any type
    void* voidp = &e;
    [[maybe_unused]]
    std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
}
```

### [`dynamic_cast`]

`virtual` 키워드가 존재하는 상속 관계에 대해 안전한 형 변환은 제공한다. 안전한 형변환을 위해 런타임에 캐스팅되며 형변환에 실패 할 경우 `nullptr`을 반환하다. 다운 캐스팅을 한다는 건 interface 설계가 잘못되었을 가능 성이 있으므로 설계를 다시 한번 검토해봐야한다.

>cpprepeference : [https://en.cppreference.com/w/cpp/language/dynamic_cast](https://en.cppreference.com/w/cpp/language/dynamic_cast)

```cpp
#include <iostream>
 
struct V
{
    virtual void f() {} // must be polymorphic to use runtime-checked dynamic_cast
};
 
struct A : virtual V {};
 
struct B : virtual V
{
    B(V* v, A* a)
    {
        // casts during construction (see the call in the constructor of D below)
        dynamic_cast<B*>(v); // well-defined: v of type V*, V base of B, results in B*
        dynamic_cast<B*>(a); // undefined behavior: a has type A*, A not a base of B
    }
};
 
struct D : A, B
{
    D() : B(static_cast<A*>(this), this) {}
};
 
struct Base
{
    virtual ~Base() {}
};
 
struct Derived: Base
{
    virtual void name() {}
};
 
int main()
{
    D d; // the most derived object
    A& a = d; // upcast, dynamic_cast may be used, but unnecessary
 
    [[maybe_unused]]
    D& new_d = dynamic_cast<D&>(a); // downcast
    [[maybe_unused]]
    B& new_b = dynamic_cast<B&>(a); // sidecast
 
    Base* b1 = new Base;
    if (Derived* d = dynamic_cast<Derived*>(b1); d != nullptr)
    {
        std::cout << "downcast from b1 to d successful\n";
        d->name(); // safe to call
    }
 
    Base* b2 = new Derived;
    if (Derived* d = dynamic_cast<Derived*>(b2); d != nullptr)
    {
        std::cout << "downcast from b2 to d successful\n";
        d->name(); // safe to call
    }
 
    delete b1;
    delete b2;
}
```

### [`reinterpret_cast`]

포인터가 다른 포인터 형식으로 변환될 수 있도록 한다. 또한 정수 계열 형식이 포인터 형식으로 변환될 수 있도록 하고 그 반대로도 변환될 수 있도록 한다.

해당 캐스팅은 컴파일 타임에 결정되며 포인터간 형변환에 대한 안전성을 보장하지 않는다.

해당 캐스팅 연산자를 사용하기 전에 다른 캐스팅 연산자를 먼저 고려해야한다.

>MSDN : [https://docs.microsoft.com/ko-kr/cpp/cpp/reinterpret-cast-operator?view=msvc-170](https://docs.microsoft.com/ko-kr/cpp/cpp/reinterpret-cast-operator?view=msvc-170)
>
>cpprepeference : [https://en.cppreference.com/w/cpp/language/reinterpret_cast](https://en.cppreference.com/w/cpp/language/reinterpret_cast)

```cpp
#include <cstdint>
#include <cassert>
#include <iostream>
 
int f() { return 42; }
 
int main()
{
    int i = 7;
 
    // pointer to integer and back
    std::uintptr_t v1 = reinterpret_cast<std::uintptr_t>(&i); // static_cast is an error
    std::cout << "The value of &i is " << std::showbase << std::hex << v1 << '\n';
    int* p1 = reinterpret_cast<int*>(v1);
    assert(p1 == &i);
 
    // pointer to function to another and back
    void(*fp1)() = reinterpret_cast<void(*)()>(f);
    // fp1(); undefined behavior
    int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
    std::cout << std::dec << fp2() << '\n'; // safe
 
    // type aliasing through pointer
    char* p2 = reinterpret_cast<char*>(&i);
    std::cout << (p2[0] == '\x7' ? "This system is little-endian\n"
                                 : "This system is big-endian\n");
 
    // type aliasing through reference
    reinterpret_cast<unsigned int&>(i) = 42;
    std::cout << i << '\n';
 
    [[maybe_unused]] const int &const_iref = i;
    // int &iref = reinterpret_cast<int&>(
    //     const_iref); // compiler error - can't get rid of const
    // Must use const_cast instead: int &iref = const_cast<int&>(const_iref);
}
```



## 람다 표현식

 람다는 가독성을 높일 수 있도록 STL 알고리즘 및 Callback 등에 이용할 수 있다.

```cpp
// STL 알고리즘에 사용
std::sort(
    vec.begin(),
    vec.end(),
    [](const int32_t& lvalue, const int32_t& rvalue) {
        return lvalue > rvalue;
    });

// Callback 사용
template <typename Predicate>
void Traverse(Predicate) {
    for (auto& [key, value] : m_container) {
        if (true == Predicate(value)) {
            break;
        }
    }
}

Traverse(
    [](const std::string& message) {
        if ("E0001" == message) {
            return false;
        }

        return true;
    });
```

전체를 캡쳐하기 보다는 필요한 변수들을 캡쳐한다.

```cpp
void Func() {
    int32_t delta_time = 10;
    int32_t damage = 100;
    Ability ability;

    ErrorCode error_code = ErrorCode::kOk;

    // 에러에 대해 함수 내에서 공통적으로 사용되는 람다 함수로 error_code 이외에는 필요하지 않다.
    auto ErrorHandler = [&error_code]() {
        Log.Error("error_code: %d\n", error_code);
        SendMessage(error_code);
    };
}
```

레퍼런스(`&`) 및 포인터(`*`)를 캡쳐할 경우 dangling-pointer 버그가 발생하지 않도록 주의해야 한다.

```cpp
Executer executer;
{
    Foo foo;
    executer.Prepare(
        [&foo]() { // 지역변수 &foo 캡쳐
            foo.Print();
        });
} // &foo는 스코프를 빠져나오면서 유효하지 않은 상태다.

// &foo에 대한 dangling-pointer 버그 발생
executer.Execute();
```

클래스 내에서 사용될 경우 `this`를 캡쳐해라.

```cpp
// SessionManager는 Process가 종료되기 직전까지 소멸되지 않는다고 가정한다.
void SessionManager::CreateSession {

    // Session 사용이 끝나는 시점에 호출될 콜백 사용
    Session sesseion(
        [this](const int32_t& sid) { // 클래스 정보를 사용하기 위해 this 포인터 캡쳐
	        this->Release(sid);
        });
}
```

함수 안에서 반복되어 사용되는 코드에 대해 람다를 활용하는 것은 괜찮으나 리팩토링 용도로 람다를 사용해서는 안된다. 또한 람다를 사용하여 가독성을 해치는 경우를 피해야한다.

```cpp
void Initilaize() {

    auto ComponentLink = [/*필요한 변수 캡쳐*/]() {
        // 각 컴포넌트 로드하여 연결
    };

    auto InitComponent = [/*필요한 변수 캡쳐*/]() {
        // 로드된 컴포넌트들을 이용해 초기화 진행
    };

    auto Run = [/*필요한 변수 캡쳐*/]() {
        // 초기화 끝난 객체들 실행
    };

    ComponentLink();

    InitComponent();

    Run();
}
```



## 템플릿(template)

`template` 파라메터는 대문자로 시작하여 각 단어의 첫 글자를 대문자로 쓰고, 언더스코어는 사용하지 않는다. 파라메터 선언 시 `typename` 타입을 사용해야하며 `class` 키워드는 사용하지 않는다.

```cpp
template <tyepname ValueType>
class Calculator {
public:
    ValueType Sum(const ValueType& value1, const ValueType& value2) {
        return value1 + value2;
    }
};

class TableData {
public:
    template <typename Consumer>
    void Traverse(const Consumer& consumer) {
        for (auto& d : container_) {
            consumer(d);            
        }
    }
private:
    std::vector<Data> container_;
};
```

템플릿 키워드 후에 공백을 넣는다. 템플릿 선언 후에는 항상 줄바꿈한다.

```cpp
// 정상
template <typename T>
T foo() {
}

// 공백이 들어가지 않아서 옳지 않다.
template<typename T>
T foo() {
}

// 템플릿 선언 후에 줄바꿈 하지 않아서 옳지 않다.
template <typename T> T foo() {
}
```

`requires`키워드는 `template`키워드와 같은 라인에 두지 않도록 개행 합니다. 개행 후 들여쓰지 않는다.

```cpp
// 정상
template <typename It>
requires Iterator<It>
void sort(It begin, It end) {
  //....
}

// 들여쓰기 되어있어서 옳지 않다.
template <typename It>
    requires Iterator<It>
void sort(It begin, It end) {
  //....
}

// template과 requires를 같은 라인에 있어 옳지 않다.
template <typename It> requires Iterator<It>
void sort(It begin, It end) {
  //....
}
```

`concept`키워드 전에 항상 개행하고, 개행 후 들여쓰지 않는다.

```cpp
// 정상
template <typename T>
concept C = ...;

// concept 이전에 개행하지 않아서 옳지 않다.
template <typename T> concept C = ...;

// 개행 후 들여쓰기 하여 옳지 않다.
template <typename T>
    concept C = ...;
```

템플릿 인수 목록에는 공백을 두지 않는다.

```cpp
// 정상
static_cast<int>(arg);
std::function<void(int)> fct;

// < > 안에 공백이 있어서 옳지 않다.
static_cast< int >(arg);
std::function< void(int) > fct;
```

