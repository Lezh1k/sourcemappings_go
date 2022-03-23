package main

import (
	"flag"
	"fmt"
	"io"
	"os"
)

type smFlags struct {
	ptrFilePath  *string
	ptrNodeIndex *int
}

func main() {
	var smf smFlags
	smf.ptrFilePath = flag.String("sm_file_path", "", "Path to file containing sourcemappings string")
	smf.ptrNodeIndex = flag.Int("sm_node_index", 0, "Index of node that should be found in sourcemappings string that will be taken from sm_file_path")
	flag.Parse()

	if smf.ptrFilePath == nil {
		fmt.Printf("Please provide file in sm_file_path argument")
		os.Exit(1)
	}

	if smf.ptrNodeIndex == nil {
		fmt.Printf("Please provide index in sm_node_index argument")
		os.Exit(2)
	}

	file, err := os.Open(*smf.ptrFilePath)
	if err != nil {
		fmt.Printf("Failed to open file %s. Error: %s\n", *smf.ptrFilePath, err.Error())
		os.Exit(3)
	}
	defer file.Close()

	buff, err := io.ReadAll(file)
	if err != nil {
		fmt.Printf("Failed to read file. Error: %s\n", err.Error())
		os.Exit(4)
	}

	node, err := sourcemappings.NodeAt(string(buff), *smf.ptrNodeIndex)
	if err != nil {
		fmt.Printf("Failed to find node at index %d. Error: %s\n", err.Error())
		os.Exit(5)
	}

	fmt.Println(node)
}
