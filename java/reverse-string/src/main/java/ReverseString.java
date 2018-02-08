class ReverseString {

    String reverse(String input) {
        String output = "";
        for (int i = input.length() - 1; i >= 0; --i) {
            output += input.charAt(i);
        }
        return output;
    }
  
}