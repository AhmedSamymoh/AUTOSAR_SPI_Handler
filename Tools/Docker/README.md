# Jenkins Docker Setup

## Usage

### Step 1: Build the Docker Image 🐋
- the image has all `CI` Tools based on `Jenkins Image` (Debian Image) 
- To build the Jenkins Docker image, run the following command:

```bash
docker build -t Brightskies_CI_Jenkins .
```
> Integrator build image once, then Open the docker container using docker compose within a server or the target machine

### Step 2: Start Jenkins with Docker Compose 🐋
- Once the image is built, start Jenkins using Docker Compose:

```bash
docker-compose up
```