🚀 DPI Engine

### Deep Packet Inspection System in C++17

A systems-level **Deep Packet Inspection (DPI) engine** that analyzes network traffic from PCAP files, performs application classification (including TLS SNI extraction), applies rule-based blocking, and generates detailed traffic reports.

Built entirely in modern C++ without external packet parsing libraries.



## 🔍 What This Project Does


Input PCAP → Parse Ethernet/IP/TCP → Extract TLS SNI → Classify Application → Apply Blocking Rules → Generate Filtered PCAP + Report



### Core Capabilities

* Raw PCAP file parsing
* Manual Ethernet / IPv4 / TCP / UDP decoding
* Five-tuple flow tracking
* TLS Client Hello inspection
* SNI extraction from HTTPS traffic
* HTTP Host header extraction
* Flow-level rule enforcement (IP / App / Domain)
* Multi-threaded packet processing pipeline
* Detailed traffic statistics output

---



## 🧠 Key Technical Concepts

### Stateful Flow Tracking

Each connection is identified using the five-tuple:

* Source IP
* Destination IP
* Source Port
* Destination Port
* Protocol

All packets of a flow share classification and blocking state.

---



### TLS SNI Extraction

Even though HTTPS payload is encrypted, the TLS Client Hello contains the domain name (SNI) in plaintext.

Example:

www.youtube.com → AppType::YOUTUBE

The engine parses TLS extensions to extract and classify domains.

---

### Flow-Level Blocking

Packet 1 (SYN) → Forward  
Packet 2 (Client Hello) → Detect YouTube → Mark flow BLOCKED  
All future packets of that flow → Dropped

Blocking is applied at connection level, not per-packet.

---

## 🏗 Architecture

### Single-Threaded Mode

Reader → Parser → Classifier → Rule Engine → Output Writer


### Multi-Threaded Mode


Reader Thread
      ↓
Load Balancer Threads
      ↓
Fast Path Worker Threads
      ↓
Output Writer Thread


Key design features:

* Consistent hashing for flow affinity
* Per-thread flow tables
* Producer–consumer model
* Thread-safe queues using mutex + condition_variable

---

## 📂 Project Structure


packet_analyzer/
├── include/
├── src/
│   ├── main_working.cpp   (Single-threaded)
│   ├── dpi_mt.cpp         (Multi-threaded)
│   ├── pcap_reader.cpp
│   ├── packet_parser.cpp
│   ├── sni_extractor.cpp
│   └── types.cpp
├── generate_test_pcap.py
└── test_dpi.pcap


---

## ⚙️ Build

### Single-threaded


g++ -std=c++17 -O2 -I include -o dpi_simple \
    src/main_working.cpp \
    src/pcap_reader.cpp \
    src/packet_parser.cpp \
    src/sni_extractor.cpp \
    src/types.cpp


### Multi-threaded


g++ -std=c++17 -pthread -O2 -I include -o dpi_engine \
    src/dpi_mt.cpp \
    src/pcap_reader.cpp \
    src/packet_parser.cpp \
    src/sni_extractor.cpp \
    src/types.cpp


---

## ▶️ Run


./dpi_engine input.pcap output.pcap


With blocking rules:


./dpi_engine input.pcap output.pcap \
    --block-app YouTube \
    --block-ip 192.168.1.50 \
    --block-domain facebook


---

## 📊 Output Includes

* Total packets processed
* Forwarded vs Dropped
* TCP vs UDP distribution
* Application breakdown
* Detected domains (SNIs)
* Thread-level statistics (multi-threaded mode)

---

## 🎯 Why This Project Matters

This project demonstrates:

* Low-level network protocol understanding
* TLS handshake inspection
* Stateful connection tracking
* Multi-threaded systems design
* Performance-oriented C++ programming
* Producer–consumer concurrency pattern

Relevant for:

* Network Security
* Systems Engineering
* Backend Infrastructure
* Cybersecurity roles

---

## 📘 Detailed Documentation

A complete technical deep-dive explaining packet structure, TLS parsing, and thread architecture is available in:

\docs\deep_technical_breakdown.md


