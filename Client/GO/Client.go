package main

import (
	"fmt"
	"log"
	"net"
	"time"
)

func main() {
	conn, err := net.Dial("tcp", ":2222")

	if err != nil {
		log.Fatal(err)
	}

	var buffer string

	fmt.Scanln(&buffer)
	conn.Write([]byte(buffer))

	recvBuffer := make([]byte, 2048)
	n, err := conn.Read(recvBuffer)

	if err != nil {
		log.Println(err)

		return
	}

	log.Println(string(recvBuffer[:n]))
	time.Sleep(time.Duration(10) * time.Second)
}
