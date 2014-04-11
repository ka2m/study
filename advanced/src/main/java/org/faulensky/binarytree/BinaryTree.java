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

package org.faulensky.binarytree;

import java.util.Stack;

public class BinaryTree<T extends Comparable<T>> {
    private Node<T> root;

    public BinaryTree() {
        root = null;
    }

    private static class Node<T extends Comparable<T>> implements Comparable<Node<T>> {
        Node<T> left;
        Node<T> right;
        T data;

        Node(T newData) {
            left = null;
            right = null;
            data = newData;
        }

        @Override
        public int compareTo(Node<T> o) {
            return data.compareTo(o.data);
        }
    }

    public void insert(T data) {
        root = insert(root, data);
    }

    public boolean lookup(int data) {
        return (lookup(root, data));
    }

    public int size() {
        return (size(root));
    }

    public void printTree() {
        displayTree();
        System.out.println();

    }


    /**
     * Recursive lookup  -- given a node, recur
     * down searching for the given data.
     */
    private boolean lookup(Node node, int data) {
        if (node == null) {
            return (false);
        }
        Node tmp = new Node(data);
        if (tmp.compareTo(node) == 0) {
            return (true);
        } else if (tmp.compareTo(node) < 0) {
            return (lookup(node.left, data));
        } else {
            return (lookup(node.right, data));
        }
    }

    private int size(Node<T> node) {
        if (node == null) return (0);
        else {
            return (size(node.left) + 1 + size(node.right));
        }
    }

    private Node<T> insert(Node<T> node, T data) {
        if (node == null) {
            node = new Node<T>(data);
        } else {
            Node<T> tmp = new Node<T>(data);
            if (tmp.compareTo(node) <= 0) {
                node.left = insert(node.left, data);
            } else {
                node.right = insert(node.right, data);
            }
        }

        return (node);
    }

    private void printTree(Node node) {
        if (node == null) return;

        printTree(node.left);
        System.out.print(node.data + "  ");
        printTree(node.right);
    }

    private void displayTree() {
        Stack<Node<T>> globalStack = new Stack<>();
        globalStack.push(root);
        int emptyLeaf = 32;
        boolean isRowEmpty = false;
        System.out.println("****......................................................****");
        while (!isRowEmpty) {
            Stack<Node<T>> localStack = new Stack<>();
            isRowEmpty = true;
            for (int j = 0; j < emptyLeaf; j++)
                System.out.print(' ');
            while (!globalStack.isEmpty()) {
                Node<T> temp = globalStack.pop();
                if (temp != null) {
                    System.out.print(temp.data);
                    localStack.push(temp.left);
                    localStack.push(temp.right);
                    if (temp.left != null || temp.right != null)
                        isRowEmpty = false;
                } else {
                    System.out.print("--");
                    localStack.push(null);
                    localStack.push(null);
                }
                for (int j = 0; j < emptyLeaf * 2 - 2; j++)
                    System.out.print(' ');
            }
            System.out.println();
            emptyLeaf /= 2;
            while (!localStack.isEmpty())
                globalStack.push(localStack.pop());
        }
        System.out.println("****......................................................****");
    }
}
