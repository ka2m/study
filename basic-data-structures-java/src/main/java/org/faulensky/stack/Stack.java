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

package org.faulensky.stack;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Stack<T> {
    protected List<T> stack;

    /**
     * Empty stack!
     */
    public Stack() {
        stack = new ArrayList<>();
    }

    /**
     * Stack with specific size
     * @param size num of elements
     */
    public Stack(int size) {
        if (size <= 0) {
            throw new IllegalArgumentException("Size cannot be negative!");
        }

        stack = new ArrayList<>(size);
    }

    /**
     * Stack with specified elements
     * @param elements list of elements
     */
    public Stack(T... elements)
    {
        stack = new ArrayList<>(Arrays.asList(elements));
    }

    public void push(T element) {
        stack.add(element);
    }

    public T pop() {
        T element = stack.get(stack.size() - 1);
        stack.remove(stack.size() - 1);
        return element;
    }

    public T front() {
        return stack.get(stack.size() - 1);
    }

    public boolean isEmpty() {
        return stack.size() == 0;
    }

    @Override
    public String toString() {
        return stack.toString();
    }
}