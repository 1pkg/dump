LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorld.cpp \
				   ../../Classes/Director.cpp \
				   ../../Classes/Resources/Cache/AudioFile.cpp \
				   ../../Classes/Resources/Cache/Cache.cpp \
				   ../../Classes/Resources/Cache/UnitedResourcesData.cpp \
				   ../../Classes/Resources/Constants/Direction.cpp \
				   ../../Classes/Resources/Constants/Policy.cpp \
				   ../../Classes/Resources/Constants/Skin.cpp \
				   ../../Classes/Resources/Constants/World.cpp \
				   ../../Classes/Resources/Data/Data.cpp \
				   ../../Classes/Resources/Data/Serializer.cpp \
				   ../../Classes/Resources/ObjectInfo.cpp \
				   ../../Classes/GameAct/Act.cpp \
				   ../../Classes/GameAct/Levels/Level.cpp \
				   ../../Classes/GameAct/Levels/Chunk.cpp \
				   ../../Classes/GameAct/Objects/Object.cpp \
				   ../../Classes/GameAct/Objects/Factories/ObjectsFactory.cpp \
				   ../../Classes/GameAct/Objects/Factories/TechFactory.cpp \
				   ../../Classes/GameAct/Objects/Interactor/Interactor.cpp \
				   ../../Classes/GameAct/Objects/SubTypes/Area.cpp \
				   ../../Classes/GameAct/Objects/SubTypes/Character.cpp \
				   ../../Classes/GameAct/Objects/SubTypes/Edge.cpp \
				   ../../Classes/GameAct/Objects/SubTypes/Shell.cpp \
				   ../../Classes/GameAct/Objects/SubTypes/Stream.cpp \
				   ../../Classes/GameAct/Objects/Tech/Ball.cpp \
				   ../../Classes/GameAct/Objects/Tech/Line.cpp \
				   ../../Classes/GameAct/Objects/Tech/Wind.cpp \
				   ../../Classes/GameAct/Objects/Tech/Saw.cpp \
				   ../../Classes/GameAct/Objects/Tech/StaticSaw.cpp \
				   ../../Classes/GameAct/Objects/Tech/Spike.cpp \
				   ../../Classes/GameAct/Objects/Tech/StaticSpike.cpp \
				   ../../Classes/GameAct/Objects/Tech/Cannon.cpp \
				   ../../Classes/GameAct/Objects/Tech/Impeller.cpp \
				   ../../Classes/ThirdParty/BodyReader/BodyReader.cpp \
				   ../../Classes/ThirdParty/Decrypter/aes_modes.c \
				   ../../Classes/ThirdParty/Decrypter/aes_ni.c \
				   ../../Classes/ThirdParty/Decrypter/aescrypt.c \
				   ../../Classes/ThirdParty/Decrypter/aeskey.c \
				   ../../Classes/ThirdParty/Decrypter/aestab.c \
				   ../../Classes/ThirdParty/Sqllite/sqlite3secure.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
