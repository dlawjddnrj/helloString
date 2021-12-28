# helloString
gdbus-codegen-glibmm 을 이용한 예제 프로젝트

build step
[아래 컴포넌트의 경로에서 build를 진행 할 디렉토리가 있다고 가정]
1. IHelloHal $ cmake .. & make -j12 install
2. HelloHal $ cmake .. & make -j12 install
3. Server $ cmake .. $ make -j12 install
4. ClientCommon $ cmake .. $ make -j12 install
5. ClientB $ cmake .. $ make -j12 install
6. qml $ qmake .. $ make -j12 install

# rule_of_five 디렉토리는 예제
# uml 디렉토리는 HelloString의 Class Diagram, Sequence Diagram이 존재함
# systemctl 명령어를 통해 HelloString Service 실행 가능

systemctl start step

