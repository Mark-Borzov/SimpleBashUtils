#!/ bin / bash

TEST_DATA_FOLDER="grep_test_files"

passed_tests=0
failed_tests=0

failed_scenarios=()
passed_scenarios=()

for file in $TEST_DATA_FOLDER/*.txt; do
  for flag in -e -i -v -c -l -n -h -s; do
    for my_pattern_search in asd '[0-9]' '[A-Z]'; do
      echo "Тест с флагом $flag с параметром $my_pattern_search в файле $file"

      grep_command="grep $flag $my_pattern_search $file"
      echo " "
      echo "Команда GREP: $grep_command"
      grep_output=$(grep $flag $my_pattern_search $file)
      echo "grep Вывод:"
      echo "$grep_output"

      s21_grep_command="./s21_grep $flag $my_pattern_search $file"
      echo " "
      echo "Команда S21_GREP: $s21_grep_command"
      s21_grep_output=$(./s21_grep $flag $my_pattern_search $file)
      echo "s21_grep Вывод:"
      echo "$s21_grep_output"

      if [ "$grep_output" == "$s21_grep_output" ]; then
      echo " "
      echo "Тест ВЫПОЛНЕН"
      passed_tests=$((passed_tests + 1))
      passed_scenarios+=("С флагом $flag с параметром '$my_pattern_search' в файле $file")
      else
      echo " "
      echo "Тест ПРОВАЛЕН"
      failed_tests=$((failed_tests + 1))
      failed_scenarios+=("С флагом $flag с параметром '$my_pattern_search' в файле $file")
      fi

      echo "-------------------------"
    done
  done
done

for file in $TEST_DATA_FOLDER/*.txt; do
  for flag in -e -i -v -c -l -n; do
    for my_pattern_search in asd '[0-9]' '[A-Z]'; do
      for file2 in $TEST_DATA_FOLDER/*.txt; do
      echo "Тест с флагом $flag с параметром $my_pattern_search в файле $file и файле2 $file2"

      grep_command="grep $flag $my_pattern_search $file $file2"
      echo " "
      echo "Команда GREP: $grep_command"
      grep_output=$(grep $flag $my_pattern_search $file $file2)
      echo "grep Вывод:"
      echo "$grep_output"

      s21_grep_command="./s21_grep $flag $my_pattern_search $file $file2"
      echo " "
      echo "Команда S21_GREP: $s21_grep_command"
      s21_grep_output=$(./s21_grep $flag $my_pattern_search $file $file2)
      echo "s21_grep Вывод:"
      echo "$s21_grep_output"

      if [ "$grep_output" == "$s21_grep_output" ]; then
      echo " "
      echo "Тест ВЫПОЛНЕН"
      passed_tests=$((passed_tests + 1))
      passed_scenarios+=("С флагом $flag с параметром '$my_pattern_search' в файле $file $file2")
      else
      echo " "
      echo "Тест ПРОВАЛЕН"
      failed_tests=$((failed_tests + 1))
      failed_scenarios+=("С флагом $flag с параметром '$my_pattern_search' в файле $file $file2")
      fi

      echo "-------------------------"
      done
    done
  done
done

echo "ИТОГ:"
echo "Выполненных тестов: $passed_tests"
echo "Ошибочных тестов: $failed_tests"
echo " "
echo "Ошибки:"
for scenario in "${failed_scenarios[@]}"; do
  echo "$scenario"
done
echo " "
echo "Выполнены:"
for scenario in "${passed_scenarios[@]}"; do
  echo "$scenario"
done
