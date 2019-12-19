# Replacing AES_ctr128_encrypt with CRYPTO_ctr128_encrypt

​	The multicompiler RNG requires openssl < v1.1.

​	If you have both openssl-1.0 and openssl-1.1 installed, you need to force cmake to recognize the 1.0 version with the following additional arguments: 

```cmake
-DOPENSSL_INCLUDE_DIR=/usr/include/openssl-1.0 

-DOPENSSL_CRYPTO_LIBRARY=/usr/lib/libcrypto.so.1.0.0
```



```shell
#!/bin/bash
replace_AES_ctr128_encrypt(){
    echo "grep -rn AES_ctr128_encrypt $1 | awk -F ":" '{print \$1}' | sort | uniq"
    target_file_list=`grep -rn AES_ctr128_encrypt $1 | awk -F ":" '{print $1}' | sort | uniq`
    echo "target_file_list=${target_file_list}"
    for f in ${target_file_list}; do
        echo "f=>${f}"
        sed -i "s/AES_ctr128_encrypt/CRYPTO_ctr128_encrypt/g" ${f}
    done
}

OPENSSL_VERSION=`openssl version | awk -F " " '{print $2}'`
echo "OPENSSL_VERSION=${OPENSSL_VERSION}"
if [ -z ${OPENSSL_VERSION} ] ;then
    exit 1
fi
V1=`echo ${OPENSSL_VERSION} | cut -d"." -f1`
V2=`echo ${OPENSSL_VERSION} | cut -d"." -f2`
V3=`echo ${OPENSSL_VERSION} | cut -d"." -f3`

ISOPENSSL1_1=1
if [ ${V1} -le 1 ];then
    if [ ${V2} -le 0 ];then
        ISOPENSSL1_1=0
    fi
fi

TargetDir=$1

if [ ${ISOPENSSL1_1} -eq 1 ];then
    if [ -z ${TargetDir} ];then
        echo "can not find target directory: ${TargetDir}"
        exit 1
    fi
    if [ -d ${TargetDir} ];then
        echo "replace_AES_ctr128_encrypt start...."
        replace_AES_ctr128_encrypt ${TargetDir}
    else
        echo "can not find target directory: ${TargetDir}"
        exit 1
    fi
else
    echo "----------------------------------------------------------------------"
    echo "[W]>>>If you have both openssl-1.0 and openssl-1.1 installed,
      you need to force cmake to recognize the 1.0 version with the additional arguments."
    echo "----------------------------------------------------------------------"
fi
```

