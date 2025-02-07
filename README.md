# Changes
 Implement DetermineXml method using stack (lifo queue).
 DetermineXml takes an XML string as input (no /n or identation)
 and returns true if the XML is properly formated, or false otherwise.
 The method is encapsulated in a dedicated namespace for scoping
 # Expected behavior:
 - Return false if the input XML string is empty.
 - Initialize the stack
 - Track the current position in the XML string with a size_t variable.
 - Iterate through the XML string
 - Check for '<' as start of a tag
 - Look for the next '>' and extract the substring in between
 - Increment the current position to the tag end.
 - Check if the tag is a closing tag. Is so compare the substring to the first tag in the stack. If different returns false
 - Discard prolog, commentq and self closing tags
 - Otherwise it should be an opening tag, push it at the top of the stack
 - Once the loop is over, check if the stack is empty, return false if not.

 # Test
 Add several test cases, covering:
 - Empty string/tags (Invalid)
 - Prolog, Comments, self closing tags (Valid)
 - More malformed tags cases (Invalid)
