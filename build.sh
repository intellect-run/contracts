#!/bin/bash

# Проверяем, задан ли аргумент
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
