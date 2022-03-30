package sourcemappings

import (
	"errors"
	"strings"
)

type Node struct {
	S, L, F, J, M string
}

func fillNode(n *Node, parts []string) {
	switch len(parts) {
	case 5:
		if parts[4] != "" {
			n.M = parts[4]
		}
		fallthrough
	case 4:
		if parts[3] != "" {
			n.J = parts[3]
		}
		fallthrough
	case 3:
		if parts[2] != "" {
			n.F = parts[2]
		}
		fallthrough
	case 2:
		if parts[1] != "" {
			n.L = parts[1]
		}
		fallthrough
	case 1:
		if parts[0] != "" {
			n.S = parts[0]
		}
	}
}

func NodeAt(input string, ix int) (Node, error) {
	var prevNode Node
	nodes_count, start := -1, 0
	for ; nodes_count < ix && start < len(input); nodes_count++ {
		tail := strings.IndexByte(input[start:], byte(';'))
		sub := input[start:]
		if tail != -1 {
			sub = input[start : start+tail]
		}
		start += tail + 1
		if len(sub) == 0 {
			continue // do nothing, we have full duplicate of previous node
		}
		parts := strings.Split(sub, ":")
		if len(parts) > 5 || len(parts) < 1 {
			return prevNode, errors.New("invalid input")
		}
		fillNode(&prevNode, parts)
	}
	return prevNode, nil
}
