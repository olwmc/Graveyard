import java.lang.String;
import java.util.ArrayList;
import java.lang.StringBuilder;
import java.util.Scanner;
import java.util.HashMap;
import java.lang.*;
import java.util.Arrays;

public class Main {
    static ArrayList < Integer > stack = new ArrayList < > ();
    // static HashMap < String, Object > environment = new HashMap < > ();
    static ArrayList < String > environment = new ArrayList<> ();
    static HashMap < String, String > words = new HashMap < > ();

    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        String input;

        while (true) {
            System.out.print("> ");
            input = keyboard.nextLine();
            parse(tokenize(input));

            // printStack(stack);
        }
    }

    public static String[] tokenize(String s) {
        return s.split(" ");
    }

    public static void parse(String[] tokens) {
        int tempMember1 = 0,
            tempMember2 = 0;

        for (int i = 0; i < tokens.length; i++) {
            if (stack.size() >= 2) {
                tempMember1 = stack.get(stack.size() - 1);r
                tempMember2 = stack.get(stack.size() - 2);
            }

            switch (tokens[i]) {
                case "?w":
                    System.out.println(words);
                    break;
                case "?e":
                    System.out.println(environment);
                    break;
                case "?s":
                    printStack(stack);
                    break;
                
                case "constant":
                    int constantValue = stack.get(stack.size() - 1);
                    String constantName = tokens[i+1];
                    i++;

                    words.put(constantName, Integer.toString(constantValue));

                    stack.remove(stack.size() - 1);
                break;

                case "@":
                case "?":
                    if(stack.size() < 0) {
                        System.out.println("Stack underflow");
                    } else {
                        int ind = stack.get(stack.size() - 1) - 1500;

                        if(ind < 0) {
                            System.out.println("Invalid reference");
                        } else {
                            String[] tempEnvArr = environment.get(ind).split("#");
                            String tempEnvValue = tempEnvArr[tempEnvArr.length - 1];
    
                            if(ind < 0) {
                                System.out.println("Invalid address");       
                            } else {
                                stack.remove(stack.size() - 1);
                                stack.add(Integer.parseInt(tempEnvValue));
                            }
                        }
                    }
                break;

                case "!":
                    /*
                        (addr value)
                    */
                    int index = stack.get(stack.size() - 1) - 1500;
                    
                    if(index < 0 || index > environment.size()) {
                        System.out.println("Invalid address");
                    } else {
                        String tempEnv = environment.get(index).split("#")[0];
                        environment.set(index, tempEnv + "#" + tempMember2);
                        doubleRem();
                    }

                break;

                case "variable":
                    environment.add(tokens[i+1] + "#" + 0);
                    i++;
                break;

                case "do":
                    if (stack.size() < 2) {
                        System.out.println("Stack Underflow");
                    } else {
                        StringBuilder loopString = new StringBuilder();
                        i++;

                        while (!tokens[i].equals("loop")) {
                            loopString.append(" " + tokens[i] + " ");
                            i++;
                        }

                        if (tempMember1 > 0 && tempMember2 > 0) {
                            for (int j = tempMember1; j < tempMember2; j++) {
                                parse(tokenize(loopString.toString().replace(" i ", Integer.toString(j))));
                            }
                        } else {
                            for (int j = tempMember2; j > tempMember1; j--) {
                                parse(tokenize(loopString.toString().replace(" i ", Integer.toString(j))));
                            }
                        }
                    }
                    break;

                case "if":
                    if (stack.size() < 1) {
                        System.out.println("Stack Underflow");
                    } else {
                        StringBuilder condString = new StringBuilder();
                        int bool = stack.get(stack.size() - 1);
                        i++;
                        boolean elseBlock = false;

                        while (!(tokens[i].equals("then"))) {
                            if (bool == -1) {
                                if (tokens[i].equals("else")) {
                                    elseBlock = true;
                                }

                                if (elseBlock == false) {
                                    condString.append(tokens[i] + " ");
                                }
                                i++;

                            } else if (bool == 0) {
                                if (tokens[i].equals("else")) {
                                    elseBlock = true;
                                }
                                i++;

                                if (elseBlock == true && !(tokens[i].equals("then"))) {
                                    condString.append(tokens[i] + " ");
                                }
                            }
                        }
                        parse(tokenize(condString.toString()));
                        stack.remove(stack.size() - 1);
                    }
                    break;

                case "mod":
                    if (stack.size() < 2) {
                        System.out.println("Stack Underflow");
                    } else {
                        doubleRem();

                        stack.add(tempMember2 % tempMember1);
                    }
                    break;

                case "and":
                    if (stack.size() < 2) {
                        System.out.println("Stack Underflow");
                    } else {
                        doubleRem();

                        if (tempMember1 == -1 && tempMember2 == -1) {
                            stack.add(-1);

                        } else {
                            stack.add(0);

                        }
                    }
                    break;

                case "or":
                    if (stack.size() < 2) {
                        System.out.println("Stack Underflow");
                    } else {
                        doubleRem();

                        if (tempMember1 == -1 || tempMember2 == -1) {
                            stack.add(-1);

                        } else {
                            stack.add(0);

                        }
                    }
                    break;

                case "invert":
                    if (stack.size() < 1) {
                        System.out.println("Stack Underflow");

                    } else {
                        int b = stack.get(stack.size() - 1);
                        stack.remove(stack.size() - 1);

                        b = (b == 0) ? -1 : 0;
                        stack.add(b);
                    }
                    break;

                case "<":
                    if (stack.size() < 2) {
                        System.out.println("Stack Underflow");

                    } else {
                        doubleRem();

                        if (tempMember1 > tempMember2) {
                            stack.add(-1);

                        } else {
                            stack.add(0);
                        }
                    }
                    break;

                case ">":
                    if (stack.size() < 2) {
                        System.out.println("Stack Underflow");

                    } else {
                        doubleRem();

                        if (tempMember1 < tempMember2) {
                            stack.add(-1);

                        } else {
                            stack.add(0);
                        }
                    }
                    break;

                case "=":
                    if (stack.size() < 2) {
                        System.out.println("Stack Underflow");

                    } else {
                        doubleRem();

                        if (tempMember1 == tempMember2) {
                            // -1 = true
                            stack.add(-1);

                        } else {
                            // 0 = false
                            stack.add(0);
                        }
                    }
                    break;

                case ".\"":
                    StringBuilder outputString = new StringBuilder();
                    boolean endOfString = false;

                    // add end of line protection
                    i++;
                    while (!endOfString) {
                        for (;(i < tokens.length) && (!endOfString); i++) {
							
                            if(tokens[i].equals('"')) {
								endOfString = true;
							} else if (!(tokens[i].length() < 1) && !tokens[i].equals("") && tokens[i].charAt(tokens[i].length() - 1) == '"') {
                                endOfString = true;
                                outputString.append(tokens[i].substring(0, tokens[i].length() - 1));

                            } else if(!endOfString) {
                                outputString.append(tokens[i]);
                                outputString.append(" ");
                            }

                        }
                    }
                    i--;

                    System.out.print(outputString.toString());
                    break;

                case "cr":
                    System.out.println();
                    break;

                case "emit":
                    if (stack.size() < 1) {
                        System.out.println("Stack Underflow");
                    } else {
                        char c = (char)(stack.get(stack.size() - 1).intValue());
                        System.out.print(c);

                        stack.remove(stack.size() - 1);
                    }
                    break;

                case ".":
                    if (stack.size() < 1) {
                        System.out.println("Stack Underflow");
                    } else {
                        System.out.print(stack.get(stack.size() - 1));
                        stack.remove(stack.size() - 1);
                    }
                    break;

                case "rot":
                    if (stack.size() < 3) {
                        System.out.println("Stack Underflow");
                    } else {
                        int tempMember3 = stack.get(stack.size() - 3);

                        doubleRem();
                        stack.remove(stack.size() - 1);

                        stack.add(tempMember1);
                        stack.add(tempMember2);
                        stack.add(tempMember3);
                    }
                    break;

                case "over":
                    if (stack.size() < 2) {
                        System.out.println("Stack Underflow");
                    } else {
                        stack.add(tempMember2);
                    }
                    break;

                case "swap":
                    if (stack.size() < 2) {
                        System.out.println("Stack Underflow");

                    } else {
                        doubleRem();

                        stack.add(tempMember1);
                        stack.add(tempMember2);
                    }
                    break;

                case "dup":
                    if (stack.size() < 1) {
                        System.out.println("Stack underflow");
                    } else {
                        stack.add(stack.get(stack.size() - 1));
                    }
                    break;

                case "drop":
                    if (stack.size() == 0) {
                        System.out.println("Stack underflow");
                    } else {
                        stack.remove(stack.size() - 1);
                    }
                    break;

                case "+":
                    if (!handleError()) {
                        doubleRem();
                        stack.add(tempMember1 + tempMember2);
                    }
                    break;

                case "*":
                    if (!handleError()) {
                        doubleRem();
                        stack.add(tempMember1 * tempMember2);
                    }
                    break;

                case ":":
                    if (i == tokens.length - 1) {
                        System.out.println("No word to define");
                    } else {
                        StringBuilder sb = new StringBuilder();
                        String wordName = tokens[i + 1];
                        i += 2;

                        while (!tokens[i].equals(";")) {
                            sb.append(tokens[i] + " ");
                            i++;
                        }

                        words.put(wordName, sb.toString());
                    }
                    break;

                case "exit":
                    System.exit(0);
                    break;

                default:
                    if (isNumeric(tokens[i])) {
                        stack.add(Integer.parseInt(tokens[i]));

                    } else if (words.containsKey(tokens[i])) {
                        parse(tokenize(words.get(tokens[i])));

                    } else if (getEnvIndex(tokens[i]) >= 0) {
                        stack.add(getEnvIndex(tokens[i]) + 1500);

                    } else if (!(tokens[i].equals("") || tokens[i].equals("\n"))) {
                        System.out.println("Unrecognized token: [" + tokens[i] + "].");
                    }
                    break;
            }
        }
    }

    public static boolean handleError() {
        if (stack.size() < 2) {
            System.out.println("Stack underflow");
            return true;
        }
        return false;
    }

    public static int getEnvIndex(String s) {
        String[] env = null;
        for(int i = 0; i < environment.size(); i++) {
            env = environment.get(i).split("#");

            if(env[0].equals(s)){
                return i;
            }
        }

        return -1;
    }
    public static void printStack(ArrayList < Integer > s) {
        StringBuilder sb = new StringBuilder();
        // sb.append("\n");
        for (int i: s) {
            sb.append(i + " ");
        }

        sb.append(" <-- Top");

        System.out.println(sb.toString());
    }

    public static boolean isNumeric(String strNum) {
        if (strNum == null) {
            return false;
        }
        try {
            double d = Integer.parseInt(strNum);
        } catch (NumberFormatException nfe) {
            return false;
        }
        return true;
    }

    public static void doubleRem(){
        stack.remove(stack.size() - 1);
        stack.remove(stack.size() - 1);
    }
}
