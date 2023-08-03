#!/bin/bash

# Переходим в директорию скрипта
cd "$(dirname "$0")"

# Разблокировка кошелька
./unlock.sh

# Получаем имя контракта из аргумента, если он есть
contract_name=$1

# Функция для установки контракта
deploy_contract() {
    local contract=$1
    local dir=$2
    local account_name=$3
    echo "Устанавливаем контракт $contract на аккаунт $account_name..."
    ./cleos.sh set contract $account_name $dir -p $account_name
}

# Если аргумент предоставлен, деплоим только этот контракт
if [ ! -z "$contract_name" ]; then
    ls ./
    echo "Проверка наличия папки для контракта $contract_name..."
    if [ -d "./$contract_name" ]; then
        echo "Папка контракта найдена. Содержимое папки:"
        deploy_contract $contract_name "/mnt/dev/contracts/$contract_name" $contract_name
    elif [ "$contract_name" == "eosio.msig" ] || [ "$contract_name" == "eosio.token" ] || [ "$contract_name" == "eosio.wrap" ]; then
        echo "Папка системного контракта найдена. Содержимое папки:"
        ls "/mnt/dev/contracts/system/build/contracts/$contract_name"
        deploy_contract $contract_name "/mnt/dev/contracts/system/build/contracts/$contract_name" $contract_name
    elif [ "$contract_name" == "eosio.system" ]; then
        echo "Папка системного контракта найдена. Содержимое папки:"
        ls "/mnt/dev/contracts/system/build/contracts/$contract_name"
        deploy_contract $contract_name "/mnt/dev/contracts/system/build/contracts/$contract_name" "eosio"
    elif [ "$contract_name" == "eosio.boot" ]; then
        echo "Папка системного контракта найдена. Содержимое папки:"
        ls "/mnt/dev/contracts/system/build/contracts/$contract_name"
        deploy_contract $contract_name "/mnt/dev/contracts/system/build/contracts/$contract_name" "eosio"
    else
        echo "Контракт $contract_name не найден"
    fi
    exit 0
fi

# Перебираем все папки с контрактами на верхнем уровне, исключая 'system'
for dir in $(find /mnt/dev/contracts/* -maxdepth 0 -type d ! -name 'system'); do
    contract=$(basename $dir)
    echo "Найдена папка $dir для контракта $contract. Содержимое папки:"
    ls $dir
    deploy_contract $contract $dir $contract
done

# Исключение для контрактов в папке system
special_system_contracts=("eosio.msig" "eosio.token" "eosio.wrap")
for contract in "${special_system_contracts[@]}"; do
    echo "Найдена папка системного контракта для $contract. Содержимое папки:"
    ls "/mnt/dev/contracts/system/build/contracts/$contract"
    deploy_contract $contract "/mnt/dev/contracts/system/build/contracts/$contract" $contract
done

deploy_contract "eosio.system" "/mnt/dev/contracts/system/build/contracts/eosio.system" "eosio"

