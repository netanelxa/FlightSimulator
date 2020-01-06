cmake_minimum_required(VERSION 3.15)
project(newEx3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(newEx3 main.cpp ConnectCommand.h ConnectCommand.cpp Lexer.cpp Lexer.h Command.cpp Command.h
        DefineVarCommand.h DefineVarCommand.cpp OpenServerCommand.h OpenServerCommand.cpp VarObj.cpp VarObj.h
        UpdateVar.cpp UpdateVar.h SleepCmd.cpp SleepCmd.h PrintCmd.cpp PrintCmd.h LoopCommand.h LoopCommand.cpp
        ConditionParser.cpp ConditionParser.h Interpreter.cpp Interpreter.h Expression.cpp Expression.h Value.cpp Value.h
        Variable.cpp Variable.h Div.cpp Div.h Minus.cpp Minus.h Mul.cpp Mul.h Plus.cpp Plus.h UMinus.cpp UMinus.h UPlus.cpp
        BinaryOperator.cpp BinaryOperator.h UnaryOperator.cpp UnaryOperator.h UpdateGeneric.cpp UpdateGeneric.h)