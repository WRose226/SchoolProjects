#Wyatt Rose#
#Project 5 - Writing Iterators in Ruby#
#This file implements a binary search tree#

class Node
    attr_accessor :value, :left, :right
    
    def initialize(value)
        @value = value
        @left = nil
        @right = nil
    end
end

class BST
    attr_accessor :root, :size, :compare

    def initialize(&block)
        @compare = block_given? ? block : proc {|x, y| x <=> y}
        @root = Node.new(nil)
        @size = 0
    end

    def add(item)
        
        if @root.value == nil
            @root.value = item 
            @size += 1
            return
        end

        addHelper(@root, item)
    end

    def empty?
        @size == 0 ? true : false
    end

    def include?(item)
        currentNode = @root

        # loop while currentNode is not nil
        while currentNode != nil

            # return true if the item is found
            return true if currentNode.value == item

            # use the compare block, 0 or 1 calls right subtree
            if @compare.call(item, currentNode.value) >= 0

                currentNode = currentNode.right
            # use the compare block, -1 calls left subtree
            else @compare.call(item, currentNode.value) < 0

                currentNode = currentNode.left
            end
        end

        return false
    end

   
    def size
        return @size
    end

    def each_inorder(&block)
        @block = block
        each_inorder_helper(@root)
    end

    

    def collect_inorder(&block)
        @block = block
        return collect_inorder_helper(@root)
    end

    

    def to_a
        to_a_helper(Array.new, @root)
    end

    

    def dup

        #create new tree
        newTree = BST.new()

        #add root to new tree
        newTree.add(@root.value)

        #call dupHelper, pass in current root, newTree root, newTree
        dupHelper(@root, newTree.root, newTree)

        return newTree
    end

    
    # contains helper methods
    private

    def addHelper(currentNode, item)

        # call the compare block, if 0 or 1 is returned, send to right subtree
        if @compare.call(item, currentNode.value) >= 0

            # if current node.right is nil, set item as new right child, increment size, return
            if (currentNode.right == nil)
                currentNode.right = Node.new(item)
                @size += 1
                return
            else
                # recursion on right subtree
                addHelper(currentNode.right, item)
            end

        # -1 is returned, send to left subtree
        else @compare.call(item, currentNode.value) < 0

            # if currentNode.left is nil, set iten as new left child, increment size, return
            if (currentNode.left == nil)
                currentNode.left = Node.new(item)
                @size += 1
                return
            else
                # recursion on left subtree
                addHelper(currentNode.left, item)
            end
        end
    end

    def each_inorder_helper(currentNode)

        # visit left node
        each_inorder_helper(currentNode.left) if currentNode.left != nil

        # send current value to block
        @block.call(currentNode.value) 

        # visit right node
        each_inorder_helper(currentNode.right) if currentNode.right != nil
    end

    def collect_inorder_helper(currentNode)
        
        # visit left node
        collect_inorder_helper(currentNode.left) if currentNode.left != nil

        # send current value to block
        currentNode.value = @block.call(currentNode.value) 

        # visit right node
        collect_inorder_helper(currentNode.right) if currentNode.right != nil
    end

    def to_a_helper(array, currentNode)
        
        # visit left node
        to_a_helper(array, currentNode.left) if currentNode.left != nil

        # add node value to array
        array.push(currentNode.value) 

        # visit right node
        to_a_helper(array, currentNode.right) if currentNode.right != nil

        return array
    end

    def dupHelper(currentNode, newTreeNode, newTree)

        #if currentNode.left exists, copy into new tree, size + 1, call recursively on left subtree
        if currentNode.left != nil

            newTreeNode.left = Node.new(currentNode.left.value)
            newTree.size += 1
            dupHelper(currentNode.left, newTreeNode.left, newTree) 
        end

        #if currentNode.right exists, copy into new tree, size + 1, call recursively on right subtree
        if currentNode.right != nil

            newTreeNode.right = Node.new(currentNode.right.value)
            newTree.size += 1
            dupHelper(currentNode.right, newTreeNode.right, newTree) 
        end
    end

end
