/*
 * Copyright 2014 Plain Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.faulensky.test;

import org.faulensky.balancedbst.SBBSTree;
import org.faulensky.linkedlist.LinkedList;
import org.faulensky.queue.Queue;
import org.faulensky.stack.Stack;
import org.junit.Assert;
import org.junit.Test;

public class MyTest {


    public void sMaxDeletion() {
        System.out.println("===============================");
        Stack<Integer> myStack = new Stack<>();
        int[] ints = {1, 2, 7, 4, 5, 6, 3};
        for (int i : ints)
            myStack.push(i);
        System.out.println("myStack: " + myStack.toString());


        int max = myStack.pop();

        Stack<Integer> tempStack = new Stack<>();
        tempStack.push(max);


        while (!myStack.isEmpty()) {
            if (myStack.front() > max)
                max = myStack.front();
            System.out.println("pop from myStack: " + myStack.front());
            tempStack.push(myStack.pop());

        }
        System.out.println("tempStack now: " + tempStack.toString());
        System.out.println("max is: " + max);
        while (!tempStack.isEmpty()) {
            int t = tempStack.pop();
            if (t != max) {
                System.out.println("push to myStack: " + t);
                myStack.push(t);
            }
        }

        System.out.println("my stack after deletion: " + myStack.toString());
        System.out.println("===============================");
        Assert.assertEquals(7, max);
    }


    public void qMaxDeletion() {
        System.out.println("===============================");
        Queue<Integer> myQ = new Queue<>();
        int[] ints = {1, 2, 7, 4, 5, 6, 3};
        for (int i : ints)
            myQ.add(i);
        System.out.println("myQueue now: " + myQ.toString());


        int max = myQ.peek();

        Queue<Integer> tempQ = new Queue<>();
        tempQ.add(max);

        while (!myQ.isEmpty()) {
            if (myQ.head() > max)
                max = myQ.head();
            System.out.println("peek from myQ: " + myQ.head());
            tempQ.add(myQ.peek());

        }
        System.out.println("tempQ now: " + tempQ.toString());
        System.out.println("max is: " + max);
        while (!tempQ.isEmpty()) {
            int t = tempQ.peek();
            if (t != max) {
                System.out.println("add to myQ: " + t);
                myQ.add(t);
            }
        }
        System.out.println("my queue after deletion: " + myQ.toString());
        System.out.println("===============================");
    }


    public void llMaxDeletion() {
        System.out.println("===============================");
        System.out.println("testing linkedlist");
        LinkedList<Integer> myLL = new LinkedList<>();
        myLL.add(45);
        myLL.add(46);
        myLL.add(6);
        myLL.add(12);

        System.out.println("now in myLL:");
        System.out.println(myLL.toString());

        Integer max = myLL.get(0);


        for (int i = 1; i < myLL.size(); i++) {
            if (myLL.get(i) > max) {
                max = myLL.get(i);
            }
        }
        System.out.println(max);

        myLL.removeElement(max);
        System.out.println(myLL.toString());

    }

    @Test
    public void bst() {
        SBBSTree bst = new SBBSTree();
        bst.insert(5);
        bst.insert(12);
        bst.insert(24);
        bst.insert(8);
        bst.insert(0);

        System.out.println("is element \"3\" exist in tree? " + bst.search(3));
        System.out.println("is element \"12\" exist in tree? " + bst.search(12));
        System.out.println("size: " + bst.countNodes());

        bst.printTree();
    }

}

