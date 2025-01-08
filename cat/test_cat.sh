#!/bin/bash

TEST_DATA_FOLDER="cat_test_files"

passed_tests=0
failed_tests=0

failed_scenarios=()
passed_scenarios=()

for file in $TEST_DATA_FOLDER/*; do
  for flag in -b -e -n -s -t ; do
    for file2 in $TEST_DATA_FOLDER/*; do
    echo "Тест с флагом $flag в файлах $file $file2"

    cat_command="cat $flag $file $file2"
    echo " "
    echo "Команда: $cat_command"
    cat_output=$(cat $flag $file $file2)
    echo "cat вывод:"
    echo "$cat_output"

    s21_cat_command="./s21_cat $flag $file $file2"
    echo " "
    echo "Команда: $s21_cat_command"
    s21_cat_output=$(./s21_cat $flag $file $file2)
    echo "s21_cat вывод:"
    echo "$s21_cat_output"

    if [ "$cat_output" == "$s21_cat_output" ]; then
      echo " "
      echo "Тест Выполнен"
      passed_tests=$((passed_tests + 1))
      passed_scenarios+=("Флаг $flag в файлах $file ")
    else
      echo " "
      echo "Тест Не Выполнен"
      failed_tests=$((failed_tests + 1))
      failed_scenarios+=("Флаг $flag в файлах $file")
    fi

    echo "-------------------------"
    done
  done
done

for file in $TEST_DATA_FOLDER/*; do
  for flag in -b -e -n -s -t; do
  echo "Тест с флагом $flag в файле $file"

  cat_command="cat $flag $file"
  echo " "
  echo "Команда: $cat_command"
  cat_output=$(cat $flag "$file")
  echo "cat вывод:"
  echo "$cat_output"

  s21_cat_command="./s21_cat $flag $file"
  echo " "
  echo "Команда: $s21_cat_command"
  s21_cat_output=$(./s21_cat $flag "$file")
  echo "s21_cat вывод:"
  echo "$s21_cat_output"

  if [ "$cat_output" == "$s21_cat_output" ]; then
    echo " "
    echo "Тест Выполнен"
    passed_tests=$((passed_tests + 1))
    passed_scenarios+=("Флаг $flag в файле $file")
  else
    echo " "
    echo "Тест Не Выполнен"
    failed_tests=$((failed_tests + 1))
    failed_scenarios+=("Флаг $flag в файле $file")
  fi

  echo "-------------------------"
  done
done

for file in $TEST_DATA_FOLDER/*; do
  echo "Тест с флагом --number-nonblank в файле $file"

  cat_command="cat -b $file"
  echo " "
  echo "Команда: $cat_command"
  cat_output=$(cat -b $file)
  echo "cat вывод:"
  echo "$cat_output"

  s21_cat_command="./s21_cat --number-nonblank $file"
  echo "Команда $s21_cat_command"
  s21_cat_output=$(./s21_cat --number-nonblank $file)
  echo "s21_cat вывод:"
  echo "$s21_cat_output"

  if [ "$cat_output" == "$s21_cat_output" ]; then
    echo " "
    echo "Тест Выполнен"
    passed_tests=$((passed_tests + 1))
    passed_scenarios+=("Флаг --number-nonblank в файле $file")
  else
    echo " "
    echo "Тест Не Выполнен"
    failed_tests=$((failed_tests + 1))
    failed_scenarios+=("Флаг --number-nonblank в файле $file")
  fi

  echo "-------------------------"
done

for file in $TEST_DATA_FOLDER/*; do
  echo "Тест с флагом --squeeze-blank в файле $file"

  cat_command="cat -s $file"
  echo " "
  echo "Команда: $cat_command"
  cat_output=$(cat -s $file)
  echo "cat вывод:"
  echo "$cat_output"

  s21_cat_command="./s21_cat --squeeze-blank $file"
  echo "Команда $s21_cat_command"
  s21_cat_output=$(./s21_cat --squeeze-blank $file)
  echo "s21_cat вывод:"
  echo "$s21_cat_output"

  if [ "$cat_output" == "$s21_cat_output" ]; then
    echo " "
    echo "Тест Выполнен"
    passed_tests=$((passed_tests + 1))
    passed_scenarios+=("Флаг --squeeze-blank в файле $file")
  else
    echo " "
    echo "Тест Не Выполнен"
    failed_tests=$((failed_tests + 1))
    failed_scenarios+=("Флаг --squeeze-blank в файле $file")
  fi

  echo "-------------------------"
done

for file in $TEST_DATA_FOLDER/*; do
  echo "Тест с флагом --number в файле $file"

  cat_command="cat -n $file"
  echo " "
  echo "Команда: $cat_command"
  cat_output=$(cat -n $file)
  echo "cat вывод:"
  echo "$cat_output"

  s21_cat_command="./s21_cat --number $file"
  echo "Команда $s21_cat_command"
  s21_cat_output=$(./s21_cat --number $file)
  echo "s21_cat вывод:"
  echo "$s21_cat_output"

  if [ "$cat_output" == "$s21_cat_output" ]; then
    echo " "
    echo "Тест Выполнен"
    passed_tests=$((passed_tests + 1))
    passed_scenarios+=("Флаг --number в файле $file")
  else
    echo " "
    echo "Тест Не Выполнен"
    failed_tests=$((failed_tests + 1))
    failed_scenarios+=("Флаг --number в файле $file")
  fi

  echo "-------------------------"
done

echo "Итог:"
echo "Выполненных тестов: $passed_tests"
echo "Ошибочных тестов: $failed_tests"
echo " "
echo "Ошибки:"
for scenario in "${failed_scenarios[@]}"; do
  echo "$scenario"
done
echo " "
echo "Выполнились:"
for scenario in "${passed_scenarios[@]}"; do
  echo "$scenario"
done
