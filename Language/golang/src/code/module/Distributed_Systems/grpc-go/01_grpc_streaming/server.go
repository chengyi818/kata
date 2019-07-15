package main

import (
	"flag"
	"fmt"
	"io"
	"math"
	"net"

	pb "code/module/Distributed_Systems/grpc-go/01_grpc_streaming/protobuf"

	grpc "google.golang.org/grpc"
)

type primeFactorsServer struct{}

func (*primeFactorsServer) PrimeFactors(stream pb.Factors_PrimeFactorsServer) error {
	fmt.Println("Entering PrimeFactors")
	for {
		req, err := stream.Recv()
		if err == io.EOF {
			break
		} else if err != nil {
			return err
		}
		fmt.Printf("Received: %d\n", req.Num)
		// time.Sleep(time.Second)
		c := make(chan int64)
		go findFactors(c, req.Num)
		for n := range c {
			resp := &pb.Response{
				Result: int64(n),
			}
			stream.Send(resp)
		}
	}
	fmt.Println("Leaving PrimeFactors")
	return nil
}

func newPrimeFactorsServer() pb.FactorsServer {
	return &primeFactorsServer{}
}

func sqrt(i int64) int64 {
	return int64(math.Sqrt(float64(i)))
}

func findFactors(c chan int64, num int64) {
	var i int64

	for i = 2; i <= sqrt(num); {
		if num%i == 0 {
			c <- i
			num = num / i
			continue
		}
		i++
	}

	if num > 1 {
		c <- num
	}
	close(c)
}

func main() {
	port := flag.Int("port", 50051, "Port for the server to run on")
	flag.Parse()

	fmt.Printf("Starting PrimeFactors Server on port %d...\n", *port)
	conn, err := net.Listen("tcp", fmt.Sprintf(":%d", *port))
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		return
	}
	grpcServer := grpc.NewServer()
	pb.RegisterFactorsServer(grpcServer, newPrimeFactorsServer())
	grpcServer.Serve(conn)
}
