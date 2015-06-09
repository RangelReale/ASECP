SET(SRCS
  ${Angelscript_SOURCE}
  
  Exceptions.cpp
  Engine.cpp
  Module.cpp
  Context.cpp
  TypeId.cpp
  ObjectType.cpp
  ObjectTypeProperty.cpp
  GlobalVar.cpp
  GlobalProperty.cpp
  Function.cpp
  FunctionParam.cpp
  Object.cpp
  ObjectProperty.cpp
  MessageEventArgs.cpp
)

SET(INCS
  ${Angelscript_HEADER}
  
  ../include/ASECP/AutoPtr.h
  ../include/ASECP/AutoState.h
  ../include/ASECP/Exceptions.h
  ../include/ASECP/Engine.h
  ../include/ASECP/Module.h
  ../include/ASECP/Context.h
  ../include/ASECP/TypeId.h
  ../include/ASECP/ObjectType.h
  ../include/ASECP/ObjectTypeProperty.h
  ../include/ASECP/GlobalVar.h
  ../include/ASECP/GlobalProperty.h
  ../include/ASECP/Function.h
  ../include/ASECP/FunctionParam.h
  ../include/ASECP/Object.h
  ../include/ASECP/ObjectProperty.h
  ../include/ASECP/Execution.h
  ../include/ASECP/Execution.tpp
  ../include/ASECP/MessageEventArgs.h
)

source_group(Script FILES ${Angelscript_HEADER} ${Angelscript_SOURCE})
source_group(ASECP REGULAR_EXPRESSION ASECP/.*)

ADD_LIBRARY(asecp STATIC ${SRCS} ${INCS} )
