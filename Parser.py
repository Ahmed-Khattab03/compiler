terminals = "=+-*/%|\\&^!#(){}[]';:,.\"~`_"
stack = []
grammar = []

def is_terminal(check):
    
    return check.islower() or check.isdigit() or check in terminals

def is_simple_grammar():
    
    for non_terminal, sttr in grammar:
        if is_terminal(non_terminal) or not is_terminal(sttr[0]):
            return False
    for i in range(0, len(grammar), 2):
        if grammar[i][1][0] == grammar[i + 1][1][0]:
            return False
    return True

def solve(input_string):
    i = 0
    while stack:
        if i == len(input_string):
            break
        top = stack.pop()
        if is_terminal(top):  
            if top == input_string[i]:
                i += 1
            else:
                return False, stack, input_string[i:]
        else:  
            rule_idx = None
            if top == 'S':
                rule_idx = 0
            elif top == 'B':
                rule_idx = 2
            else:
                return False, stack, input_string[i:]
            
            if input_string[i] == grammar[rule_idx][1][0]:
                selected_rule = grammar[rule_idx]
            elif input_string[i] == grammar[rule_idx + 1][1][0]:
                selected_rule = grammar[rule_idx + 1]
            else:
                return False, stack, input_string[i:]
            
            
            for char in reversed(selected_rule[1]):
                stack.append(char)
    
    return len(stack) == 0 and i == len(input_string), stack, input_string[i:]

def main():
    while True:
        global grammar, stack
        grammar = [
            ('S', ''), ('S', ''), 
            ('B', ''), ('B', '')
        ]
        for i in range(4):
            non_terminal = 'S' if i < 2 else 'B'
            grammar[i] = (non_terminal, input(f"Enter rule number {i + 1} for non-terminal '{non_terminal}': ").strip())
        
        if not is_simple_grammar():
            print("This is not a simple grammar")
            continue
        
        while True:
            input_string = input("Enter the string to be checked: ").strip()
            print(f"The input string: {[f'{char}' for char in input_string]}")
            stack = ['S']
            
            accepted, final_stack, remaining_input = solve(input_string)
            
            print(f"Stack after checking: {[char for char in reversed(final_stack)]}")
            print(f"The rest of the unchecked string: {[char for char in remaining_input]}")
            if accepted:
                print("The input string is Accepted.")
            else:
                print("The input string is Rejected.")
            
            print("1- Another grammar.\n2- Another string.\n3- Exit.")
            choice = int(input("Enter your choice: ").strip())
            if choice == 1:
                break
            elif choice == 3:
                return

if __name__ == "__main__":
    main()
