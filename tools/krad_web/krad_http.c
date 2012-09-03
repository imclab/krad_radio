#include "krad_http.h"

#include "krad_radio.html.h"
#include "krad_radio.js.h"

krad_http_client_t *krad_http_create_client(krad_http_t *krad_http) {

	krad_http_client_t *client = calloc(1, sizeof(krad_http_client_t));

	client->krad_http = krad_http;
	
	return client;

}

void krad_http_destroy_client (krad_http_t *krad_http, krad_http_client_t *client) {

	//printf("Destroy client!!\n");
	
	close (client->sd);
		
	//if (client->file_fd) {
	//	close (client->file_fd);
	//}
		
	free (client);
	
	printk ("HTTP Client done.");
	
	pthread_exit(0);	

}

void krad_http_write_headers (krad_http_client_t *client, char *content_type) {

	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "HTTP/1.1 200 OK\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Status: 200 OK\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Connection: close\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Server: Krad-Radio\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Content-Type: %s; charset=utf-8\r\n", content_type);
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "\r\n");

	client->wrote = write (client->sd, client->out_buffer, strlen(client->out_buffer));

}

void krad_http_write_file_headers (krad_http_client_t *client, char *content_type, unsigned int length) {

	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "HTTP/1.1 200 OK\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Server: Krad-Radio\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Content-Length: %d\r\n", length);
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Content-Type: %s\r\n", content_type);
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "\r\n");

	client->wrote = write (client->sd, client->out_buffer, strlen(client->out_buffer));

}

void krad_http_404 (krad_http_client_t *client) {

	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "HTTP/1.1 404 Not Found\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Status: 404 Not Found\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Connection: close\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Server: Krad-Radio\r\n");	
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "Content-Type: text/html; charset=utf-8\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "\r\n");
	client->out_buffer_pos += sprintf(client->out_buffer + client->out_buffer_pos, "404 Not Found");
	
	client->wrote = write (client->sd, client->out_buffer, strlen(client->out_buffer));
	
	krad_http_destroy_client(client->krad_http, client);
	
}


/*

void upload(int fd) {
	int file_fd = 0, buflen = 0, wrote = 0, end = 0, ret = 0, bufpos = 0, wrote_total = 0, length = 0, status;
	
	static char buffer[8192];
 
 	char station[256];
 	char filename[512];
	char fullfilename[768];

	struct stat st;

	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	
	printf("\nNew Upload\n");
	
	ret = read(fd,buffer,BUFSIZE); 	 
	
	if (ret == 0 || ret == -1) {	 
		printf("failed to read browser request\n");
		exit(1);
	}
	
	buflen = BUFSIZE / 2;

	while(bufpos <= buflen) {
		if (strncmp(buffer + bufpos, "Content-Length: ", 15) == 0) {
			length = atoi(buffer + 15 + bufpos);
			printf("Upload Size: %dK\n", length / 1000);
		}

		if (strncmp(buffer + bufpos, "X-File-Name: ", 13) == 0) {
			end = strcspn(buffer + bufpos + 13, "\r");
			strncpy(filename, buffer + bufpos + 13, end);
			filename[end] = '\0';
			printf("Filename: %s\n", filename);
		}
		
		if (strncmp(buffer + bufpos, "X-Krad-Station: ", 16) == 0) {
			strncpy(station, buffer + bufpos + 16, strcspn(buffer + bufpos + 16, "\r"));
			printf("Station %s\n", station);
		}
		
		bufpos += strcspn(buffer + bufpos, "\r") + 2;
		//printf("spin %d - %d\n", bufpos, buflen);
		if (strncmp(buffer + bufpos, "\r\n", 2) == 0) {
			bufpos = bufpos + 2;
			printf("Headers Length: %d\n", bufpos );
			break;
		}		
	}


	// test dir existance
	sprintf(fullfilename, "%s/krad/uploads/%s", homedir, station);
	if(stat(fullfilename, &st) == 0) {
		printf("Directory Exists: %s\n", fullfilename );
	} else {
		status = mkdir(fullfilename, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (status == 0) {	
			printf("Directory Created: %s\n", fullfilename );
		} else {
			printf("Cant create directory: %s\n", fullfilename );
		}	
	}

	sprintf(fullfilename, "%s/krad/uploads/%s/%s", homedir, station, filename);

	if ((file_fd = open(fullfilename, O_WRONLY | O_CREAT, mode)) == -1) {
		printf("failed to open new file");
		exit(1);
	}


	wrote = write(file_fd, buffer + bufpos, ret - bufpos);
	wrote_total += wrote;
	//printf("wrote %d bytes total %d\n", wrote, wrote_total);

	while (wrote_total != length) {

		if (wrote_total > length) {	 
			printf("failed got to much data\n");
			close(file_fd);
			close(fd);
			exit(1);
		}

		ret = read(fd, buffer, BUFSIZE);
		
		if (ret == 0 || ret < 0) {	 
			printf("failed to read incomping socket\n");
			close(file_fd);
			close(fd);
			exit(1);
		}
		
		wrote = write(file_fd, buffer, ret);
		wrote_total += wrote;
	}

	close(file_fd);
	close(fd);

	printf("Upload Complete %s - %dKB / %dMB for station %s\n", fullfilename, wrote_total / 1000, (wrote_total / 1000 / 1000), station);

	tell_station_about_upload(station, fullfilename);


	exit(0);
}


*/

void *krad_http_client_thread (void *arg) {


	krad_http_client_t *client = (krad_http_client_t *)arg;
	
	int ret;
	int wrote;
	int wrot;
	int wrote_total;
	unsigned int length;
	int fd;
	struct stat file_stat;	
	
	wrote_total = 0;
	
	
	//printf("\nNew Web Client\n");
	
	/*
	struct pollfd sockets[1];	
	int flags;
	
	flags = fcntl (client->sd, F_GETFL, 0);

	if (flags == -1) {
		close (client->sd);
		return NULL;
	}

	flags |= O_NONBLOCK;

	flags = fcntl (client->sd, F_SETFL, flags);
	if (flags == -1) {
		close (client->sd);
		return NULL;
	}
	
	sockets[0].fd = client->sd;
	sockets[0].events = POLLIN;
	
	client->ret = poll (sockets, 1, 250);
	*/

	client->ret = read (client->sd, client->in_buffer + client->in_buffer_pos, BUFSIZE);		
	
	if (client->ret == 0 || client->ret == -1) {
		printke ("failed to read browser request");
		krad_http_destroy_client(client->krad_http, client);
	}

	
	printkd ("Krad HTTP Request: %s", client->in_buffer);
	
	while (client->in_buffer_pos <= 256) {
	
		if (strncmp(client->in_buffer, "GET /", 5) == 0) {
	
			client->ret = strcspn (client->in_buffer + client->in_buffer_pos + 5, "\r ?");
			memcpy (client->get, client->in_buffer + client->in_buffer_pos + 5, client->ret);
			client->get[client->ret] = '\0';
		
			//printf("Wanted: %s\n", client->get);
		
			if (strncmp("favicon.ico", client->get, 11) == 0) {
		
				//printf("favicon web client done\n");

				krad_http_destroy_client(client->krad_http, client);

			}
		
			if (strncmp("krad_radio.js", client->get, 13) == 0) {

				krad_http_write_headers (client, "text/javascript");


				client->wrote = write(client->sd, client->krad_http->js, client->krad_http->js_len);

		
				//printf("js web client done\n");

				krad_http_destroy_client (client->krad_http, client);


			}
		
			if ((strlen(client->get) == 0) || (strncmp("krad_radio.html", client->get, 15) == 0)) {

				krad_http_write_headers (client, "text/html");

				client->wrote = write(client->sd, client->krad_http->html, client->krad_http->html_len);
		
				//printf("html web client done\n");

				krad_http_destroy_client (client->krad_http, client);

			}
			
			if (strncmp("snapshot", client->get, 8) == 0) {

				if ((fd = open("/home/oneman/testy/snapshot_1346676086_8324.jpg", O_RDONLY)) > -1) {
		
					fstat (fd, &file_stat);
		
					length = file_stat.st_size;
					
					krad_http_write_file_headers (client, "image/jpeg", length);

					while (wrote_total != length) {

						ret = read (fd, client->out_buffer, BUFSIZE);
		
						if (ret <= 0) {
							close(fd);
							krad_http_destroy_client (client->krad_http, client);
						}
		
						wrote = 0;
		
						while (wrote != ret) {
						
							wrot = write (client->sd, client->out_buffer + wrote, ret - wrote);
						
							if (wrot <= 0) {
								close(fd);
								krad_http_destroy_client (client->krad_http, client);
							}
							wrote += wrot;
							wrote_total += wrote;			
						
						}
		
						
					}
					close (fd);
				}

				krad_http_destroy_client (client->krad_http, client);

			}
			
			krad_http_404 (client);
		
		}
		
		client->in_buffer_pos += strcspn(client->in_buffer + client->in_buffer_pos, "\r") + 2;
		//printf("spin %d\n", client->in_buffer_pos);
		if (strncmp(client->in_buffer + client->in_buffer_pos, "\r\n", 2) == 0) {
			client->in_buffer_pos = client->in_buffer_pos + 2;
			//printf("Headers Length: %d\n", client->in_buffer_pos );
			break;
		}		
		
	}

	printke ("Krad HTTP client fail");

	krad_http_destroy_client (client->krad_http, client);
	
	return NULL;
	
}


void krad_http_server_destroy (krad_http_t *krad_http) {

	printkd ("krad_http Shutting Down");

	if (krad_http != NULL) {
	
		krad_http->shutdown = 1;

		usleep (25000);
	
		pthread_cancel (krad_http->server_thread);

		close (krad_http->listenfd);

		free (krad_http);

	}

}

void *krad_http_server_run (void *arg) {

	krad_http_t *krad_http = (krad_http_t *)arg;

	krad_http_client_t *newclient;
	socklen_t length;
	static struct sockaddr_in cli_addr;

	while (!krad_http->shutdown) {
	
	
		newclient = krad_http_create_client(krad_http);
	
		length = sizeof(cli_addr);
		
		if ((krad_http->socketfd = accept(krad_http->listenfd, (struct sockaddr *)&cli_addr, &length)) < 0) {
			close (krad_http->listenfd);
			failfast ("krad_http socket error on accept mayb a signal or such\n");
		}

		newclient->sd = krad_http->socketfd;

		pthread_create (&newclient->client_thread, NULL, krad_http_client_thread, (void *)newclient);
		pthread_detach (newclient->client_thread);

	}
	
	return NULL;
	
}

krad_http_t *krad_http_server_create (int port, int websocket_port) {
	
	krad_http_t *krad_http = calloc(1, sizeof(krad_http_t));

	static struct sockaddr_in serv_addr;
	int on = 1;
	char string[7];

	krad_http->port = port;
	krad_http->websocket_port = websocket_port;
	
	krad_http->js = (char *)tools_krad_web_res_krad_radio_js;
	krad_http->html = (char *)tools_krad_web_res_krad_radio_html;
	krad_http->js_len = tools_krad_web_res_krad_radio_js_len;
	krad_http->html_len = tools_krad_web_res_krad_radio_html_len;
	
	snprintf (string, 7, "%6d", krad_http->websocket_port);		
	memcpy (strstr (krad_http->html, "WSPORT"), string, 6);	
	
	if (krad_http->port < 0 || krad_http->port > 65535) {
		failfast ("krad_http port number error\n");
	}
	
	printk ("Krad Web Starting Up on port %d", krad_http->port);

	krad_http->homedir = getenv ("HOME");
 	
 	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(krad_http->port);
 	
	/* setup the network socket */
	if ((krad_http->listenfd = socket(AF_INET, SOCK_STREAM,0)) < 0) {
		failfast ("krad_http system call socket error");
	}
	
	if ((setsockopt (krad_http->listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on))) < 0) {
		close (krad_http->listenfd);
		failfast ("kradweb system call setsockopt error");
	}
	
	if (bind (krad_http->listenfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0) {
		close (krad_http->listenfd);
		failfast ("krad_http system call bind error\n");
	}

	if (listen (krad_http->listenfd, SOMAXCONN) <0) {
		close (krad_http->listenfd);
		failfast ("krad_http system call bind error\n");
	}

	pthread_create (&krad_http->server_thread, NULL, krad_http_server_run, (void *)krad_http);
	pthread_detach (krad_http->server_thread);

	return krad_http;

}
