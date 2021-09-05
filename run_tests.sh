EXEC=$1
TMP_OUT=$2

echo "Executando testes:"
for i in {1..5..1}; do
  testname=$(printf "%02d" $i)
  $EXEC < tests/$testname.in > $TMP_OUT
  if ! diff -qwB tests/$testname.out $TMP_OUT &>/dev/null; then
    echo "Test $testname failed"
  else
    echo "Test $testname passed"
  fi
done
