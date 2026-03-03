# Containerized Lab Environment

This project explores containerization concepts through practical experiments using Docker, Docker Compose and Linux namespaces.

It includes a small C program that demonstrates low-level container mechanisms such as PID and mount namespaces, combined with a chroot environment.

## Technologies

- Docker
- Docker Compose
- C
- Linux namespaces
- chroot

## Features

- Deployment of containerized services with Docker
- Service orchestration with Docker Compose
- Experimentation with Linux namespaces (PID, mount, network, UTS)
- Minimal container-like environment using chroot

## Docker & Docker Compose (OpenStack VM)

Docker and Docker Compose experiments were conducted on a lab VM deployed on OpenStack.
The VM environment is no longer available, but the repository documents the approach and key configurations.

## Purpose

The goal of this lab is to better understand how container technologies work internally and how isolated environments can be created on Linux systems.
