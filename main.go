package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"os"
	"sourcemappings/sourcemappings"
)

func main() {
	var reader = bufio.NewReader(os.Stdin)
	var buff, _ = reader.ReadString('\n')
	sm, err := sourcemappings.NodeAt(buff)
	if err != nil {
		fmt.Printf("Failed to decompress. Error: %s\n", err.Error())
		os.Exit(5)
	}

	output, err := json.Marshal(&sm)
	if err != nil {
		fmt.Println("failed to marshal result to JSON")
		os.Exit(6)
	}
	fmt.Print(string(output))

	//_ = ioutil.WriteFile(*smf.ptrOutputFilePath, output, 0644)
}
