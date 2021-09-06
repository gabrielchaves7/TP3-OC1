EXEC=$1

echo "Executando testes:"
for i in 1 2 3 4 5; do
  testname=$(printf "%02d" $i)
  $EXEC tests/$testname.in result.$testname
  if ! diff -qwB tests/$testname.out result.$testname &>/dev/null; then
    echo "Test $testname failed"
  else
    echo "Test $testname passed"
  fi
done
