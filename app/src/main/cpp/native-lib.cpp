#include <jni.h>
#include <string>
#include "external/jni_bind/jni_bind.h"
#include "external/math2/include/math2.h"
#include <another_file.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_ir_erfansn_nativecodeplayground_MainActivity_concatenateMembersNameJni(JNIEnv *env, jobject thiz, jobject company) {
    std::string names;

    auto companyClass = env->FindClass("ir/erfansn/nativecodeplayground/Company");
    auto staffsFieldId = env->GetFieldID(companyClass, "staffs", "Ljava/util/List;");
    auto staffsJObject = env->GetObjectField(company, staffsFieldId);
    auto listClass = env->FindClass("java/util/List");
    auto listSizeMethodId = env->GetMethodID(listClass, "size", "()I");
    auto listSize = env->CallIntMethod(staffsJObject, listSizeMethodId);
    auto listGetMethodId = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
    for (int i = 0; i < listSize; ++i) {
        auto staff = (jstring) env->CallObjectMethod(staffsJObject, listGetMethodId, i);
        names += env->GetStringUTFChars(staff, nullptr);
    }

    auto sum = plus(1, 2);

    return env->NewStringUTF(names.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_ir_erfansn_nativecodeplayground_MainActivity_concatenateMembersNameJniBind(JNIEnv *env, jobject thiz, jobject company) {
    std::string names;

    auto jvm{std::make_unique<jni::JvmRef<jni::kDefaultJvm>>(env)};

    constexpr jni::Class jList {
            "java/util/List∑œ",
            jni::Method{"get", jni::Return{jni::Class{"java/lang/Object"}}, jni::Params<jint>{}},
            jni::Method{"size", jni::Return<jint>{}},
    };
    static constexpr jni::Class jCompany {
            "ir/erfansn/nativecodeplayground/Company",
            jni::Field{"staffs", jList}
    };

    auto companyWrapper = jni::LocalObject<jCompany>{company};
    auto staffs = companyWrapper.Access<"staffs">().Get();
    for (int i = 0; i < staffs.Call<"size">(); ++i) {
        auto nameObject = staffs.Call<"get">(i);
        auto name = jni::LocalString{nameObject.Release()};
        names += std::string(name.Pin().ToString());
    }

    auto hello_name = hello();

    return env->NewStringUTF(names.c_str());
}
