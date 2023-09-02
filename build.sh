#!/bin/bash

# Получение ветки из аргументов командной строки
while getopts ":n:" opt; do
  case $opt in
    n)
      branch="$OPTARG"
      ;;
    \?)
      echo "Неверный параметр: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Параметр -$OPTARG требует аргумента." >&2
      exit 1
      ;;
  esac
done

# Проверка наличия заданной ветки
if [ -n "$branch" ]; then
  # Переключение на заданную ветку
  git checkout "$branch"
  # Мерж изменений из master в текущую ветку
  git merge master
fi

# Проверяем, задан ли аргумент для контрактов
if [ "$1" != "" ]; then
  contracts=$1
else
  contracts="*"
fi

# Счетчик контрактов
count=0

# Запуск контейнера Docker
docker run --rm --name cdt_v4.0.0 \
    --volume $(pwd):/project \
    -w /project \
    dacomfoundation/cdt_v4.0.0 /bin/bash -c "

# Перебираем все папки в директории
for folder in $contracts/ ; do
  # Убираем слэш из названия папки, чтобы получить имя контракта
  contract=\${folder%/}
  contract=\${contract##*/}

  echo \"Сборка контракта \$contract в \$folder...\"

  # Переходим в директорию контракта
  cd \$folder

  # Проверяем, является ли контракт 'system'
  if [ \"\$contract\" = \"system\" ]; then
    # Если да, запускаем build.sh внутри этой папки
    ./build.sh
  else
    # Если нет, компилируем как обычно
    cdt-cpp -abigen -I include -R include -contract \$contract -o \$contract.wasm \$contract.cpp
  fi
  
  # Возвращаемся назад
  cd ..

  echo \"Сборка контракта \$contract завершена!\"
  count=\$((count+1))
done

echo \"Успешно завершена сборка \$count контрактов!\"
"
