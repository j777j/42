# Test for environment variables and exit status

# 1. Set a variable and check if it exists
export MY_VAR="is_set"
env | grep MY_VAR

# 2. Unset the variable and check if it's gone
unset MY_VAR
env | grep MY_VAR

# 3. Test exit status
# Run a failing command
ls /no/such/dir
# Check the exit status (should be non-zero)
echo $?

# Run a succeeding command
ls / > /dev/null
# Check the exit status (should be 0)
echo $?
