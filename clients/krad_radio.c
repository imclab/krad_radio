#include "kr_client.h"

void krad_radio_command_help () {
  printf ("krad_radio STATION_SYSNAME COMMAND OPTIONS...");
  printf ("\n\n");
  printf ("Commands:\n");
  printf ("launch destroy info tag tags stag remoteon remoteoff webon weboff oscon oscoff\n");
  printf ("setdir ls lm lc tone input output plug unplug map mixmap xmms2 noxmms2 mix\n");
  printf ("transmitter_on transmitter_off closedisplay display receiver_on receiver_off\n");
  printf ("comp res fps snap jsnap play record capture\n");
}

int get_logname (kr_client_t *client, char *logname, int max) {

  kr_crate_t *crate;
  crate = NULL;
  int wait_ms;
  int ret;
  
  kr_system_info (client);
  wait_ms = 250;
  ret = 0;

  while (kr_delivery_wait_until_final (client, wait_ms)) {
    kr_delivery_get (client, &crate);
    if (crate != NULL) {
      if (kr_crate_loaded (crate)) {
        if ((crate->addr->path.unit == KR_STATION) && (crate->addr->path.subunit.zero == KR_STATION_UNIT)) {
          ret = strlen(crate->inside.radio->logname);
          if (ret > 0) {
            if (ret < max) {
              strncpy (logname, crate->inside.radio->logname, max);
            } else {
              ret = 0;
            }
          }
        }
      }
      kr_crate_recycle (&crate);
    }
  }
  return ret;
}

void print_logname (kr_client_t *client) {

  char logname[256];

  if (get_logname (client, logname, 256)) {
    printf ("%s\n", logname);
  }
}

void tail_log (kr_client_t *client, int lines, int dofollow) {

  int ret;
  char logname[256];
  char last[32];
  char *args[6];
  
  if (lines < 0) {
    lines = 0;
  }
  
  snprintf (last, sizeof (last), "%d", lines);

  if (get_logname (client, logname, 256)) {
    kr_client_destroy (&client);
    args[0] = "tail";
    args[1] = "-n";
    args[2] = last;
    if (dofollow == 1) {
      args[3] = "-f";
      args[4] = logname;
      args[5] = NULL;    
    } else {
      args[3] = logname;
      args[4] = NULL;
    }
    ret = execv ("/usr/bin/tail", args);
    if (ret == -1) {
      printf ("Error running tail...\n");
    }
    exit (1);
  }
}

int main (int argc, char *argv[]) {

  kr_client_t *client;
  char *sysname;
  int ret;
  int val;
  kr_unit_control_t uc;

  sysname = NULL;
  client = NULL;
  ret = 0;
  val = 0;

  if ((argc == 1) || (argc == 2)) {
    if (argc == 2) {
      if (((strlen(argv[1]) == 2) && (strncmp(argv[1], "vn", 2) == 0)) ||
          ((strlen(argv[1]) == 3) && (strncmp(argv[1], "-vn", 3) == 0)) ||
          ((strlen(argv[1]) == 4) && (strncmp(argv[1], "--vn", 4) == 0))) {
          printf("%d\n", VERSION_NUMBER);
          return 0;
      }

      if (((strlen(argv[1]) == 2) && (strncmp(argv[1], "gv", 2) == 0)) ||
          ((strlen(argv[1]) == 2) && (strncmp(argv[1], "vg", 2) == 0)) ||
          ((strlen(argv[1]) == 3) && (strncmp(argv[1], "-vg", 3) == 0)) ||
          ((strlen(argv[1]) == 3) && (strncmp(argv[1], "git", 3) == 0)) ||
          ((strlen(argv[1]) == 4) && (strncmp(argv[1], "--vg", 4) == 0)) ||
          ((strlen(argv[1]) == 6) && (strncmp(argv[1], "gitver", 6) == 0)) ||
          ((strlen(argv[1]) == 10) && (strncmp(argv[1], "gitversion", 10) == 0))) {
          printf("%s\n", KRAD_GIT_VERSION);
          return 0;
      }

      if (((strlen(argv[1]) == 1) && (strncmp(argv[1], "v", 1) == 0)) ||
          ((strlen(argv[1]) == 2) && (strncmp(argv[1], "-v", 2) == 0)) ||
          ((strlen(argv[1]) >= 3) && (strncmp(argv[1], "--v", 3) == 0))) {

          printf (KRAD_VERSION_STRING "\n");
          return 0;
      }

      if ((strlen(argv[1]) == 2) && (strncmp(argv[1], "ls", 2) == 0)) {
        if (printf ("%s", krad_radio_running_stations ())) {
          printf ("\n");
        }
        return 0;
      }
    }

    krad_radio_command_help ();
    return 0;
  }

  if (krad_valid_host_and_port (argv[1])) {
    sysname = argv[1];
  } else {
    if (!krad_valid_sysname(argv[1])) {
      fprintf (stderr, "Invalid station sysname!\n");
      return 1;
    } else {
      sysname = argv[1];
    }
  }

  if ((strncmp(argv[2], "launch", 6) == 0) || (strncmp(argv[2], "load", 4) == 0)) {
    krad_radio_launch (sysname);
    return 0;
  }

  if ((strncmp(argv[2], "destroy", 7) == 0) || (strncmp(argv[2], "kill", 4) == 0)) {
    ret = krad_radio_destroy (sysname);
    if (ret == 0) {
      printf ("Daemon shutdown\n");
    }
    if (ret == 1) {
      printf ("Daemon was killed\n");
    }
    if (ret == -1) {
      printf ("Daemon was not running\n");
    }
    return 0;
  }

  client = kr_client_create ("krad command line client");

  if (client == NULL) {
    fprintf (stderr, "Could create client\n");
    return 1;
  }

  if (!kr_connect (client, sysname)) {
    fprintf (stderr, "Could not connect to %s krad radio daemon\n", sysname);
    kr_client_destroy (&client);
    return 1;
  }

  /* Krad Radio Commands */

  if ((strncmp(argv[2], "ls", 2) == 0) && (strlen(argv[2]) == 2)) {
    if (argc == 3) {
      //FIXME
      //kr_transponder_list (client);
      //kr_delivery_accept_and_report (client);

      kr_remote_list (client);
      kr_delivery_accept_and_report (client);

      kr_transponder_adapters (client);
      kr_delivery_accept_and_report (client);
      
      kr_compositor_subunit_list (client);
      kr_delivery_accept_and_report (client);

      kr_mixer_portgroup_list (client);
      kr_delivery_accept_and_report (client);          
    }
  }

  if ((((strncmp(argv[2], "lsv", 3) == 0) || 
        (strncmp(argv[2], "lsd", 3) == 0) ||
        (strncmp(argv[2], "lsa", 3) == 0)) &&
        (strlen(argv[2]) == 3)) || (strncmp(argv[2], "adapters", 8) == 0)) {
    if (argc == 3) {
      kr_transponder_adapters (client);
      kr_delivery_accept_and_report (client);
    }
  }

  if ((strncmp(argv[2], "info", 4) == 0) || (strncmp(argv[2], "sys", 3) == 0)) {
    kr_system_info (client);
    kr_delivery_accept_and_report (client);
  }

  if (strncmp(argv[2], "cpu", 4) == 0) {
    //FIXME
    //kr_delivery_accept_and_report (client);
  }

  if (strncmp(argv[2], "uptime", 6) == 0) {
    //FIXME
    //kr_delivery_accept_and_report (client);
  }
  
  if (strncmp(argv[2], "setdir", 6) == 0) {
    if (argc == 4) {
      kr_set_dir (client, argv[3]);
    }
  }

  if (strncmp(argv[2], "log", 3) == 0) {
    print_logname (client);
  }
  
  if ((strncmp(argv[2], "tailf", 5) == 0) || (strncmp(argv[2], "ftail", 5) == 0)) {
    if (argc == 3) {
      tail_log (client, 25, 1);
    }
    if (argc == 4) {
      tail_log (client, atoi(argv[3]), 1);
    }    
  }

  if (strncmp(argv[2], "tail", 4) == 0) {
    if (argc == 3) {
      tail_log (client, 25, 0);
    }
    if (argc == 4) {
      tail_log (client, atoi(argv[3]), 0);
    }    
  }

  if (strncmp(argv[2], "tags", 4) == 0) {

    if (argc == 3) {
      kr_tags (client, NULL);    
      kr_delivery_accept_and_report (client);
    }
    if (argc == 4) {
      kr_tags (client, argv[3]);    
      kr_delivery_accept_and_report (client);
    }          

  } else {
    if (strncmp(argv[2], "tag", 3) == 0) {
      if (argc == 4) {
        kr_tag (client, NULL, argv[3]);
        kr_delivery_accept_and_report (client);
      }
      if (argc == 5) {
        kr_tag (client, argv[3], argv[4]);
        kr_delivery_accept_and_report (client);            
      }    
    }
  }

  if (strncmp(argv[2], "stag", 4) == 0) {
    if (argc == 5) {
      kr_set_tag (client, NULL, argv[3], argv[4]);
    }
    if (argc == 6) {
      kr_set_tag (client, argv[3], argv[4], argv[5]);
    }
  }

  if (((strlen(argv[2]) == 6) && (strncmp(argv[2], "remote", 6) == 0)) || 
      ((strlen(argv[2]) == 7) && (strncmp(argv[2], "remotes", 7) == 0))) {
    kr_remote_list (client);
    kr_delivery_accept_and_report (client);
  }
    
  if ((strncmp(argv[2], "remoteon", 8) == 0) || (strncmp(argv[2], "remote_on", 9) == 0)) {
    ret = 0;
    if (argc == 4) {
      ret = kr_remote_on (client, NULL, atoi(argv[3]));
    }
    if (argc == 5) {
      ret = kr_remote_on (client, argv[3], atoi(argv[4]));
    }
    if (ret == -1) {
      printf ("Invalid Port Specified\n");
    }
  }  

  if ((strncmp(argv[2], "remoteoff", 9) == 0) || (strncmp(argv[2], "remote_off", 10) == 0)) {
    ret = 0;
    if (argc == 3) {
      ret = kr_remote_off (client, NULL, 0);
    }
    if (argc == 4) {
      ret = kr_remote_off (client, NULL, atoi(argv[3]));
    }
    if (argc == 5) {
      ret = kr_remote_off (client, argv[3], atoi(argv[4]));
    }
    if (ret == -1) {
      printf ("Invalid Port Specified\n");
    }
  }

  if (strncmp(argv[2], "webon", 5) == 0) {
    if (argc == 5) {
      kr_web_enable (client, atoi(argv[3]), atoi(argv[4]), "", "", "");
    }
    if (argc == 6) {
      kr_web_enable (client, atoi(argv[3]), atoi(argv[4]), argv[5], "", "");
    }
    if (argc == 7) {
      kr_web_enable (client, atoi(argv[3]), atoi(argv[4]), argv[5], argv[6], "");
    }
    if (argc == 8) {
      kr_web_enable (client, atoi(argv[3]), atoi(argv[4]), argv[5], argv[6], argv[7]);
    }
  }      

  if (strncmp(argv[2], "weboff", 6) == 0) {
    if (argc == 3) {
      kr_web_disable (client);
    }
  }

  if (strncmp(argv[2], "oscon", 5) == 0) {
    if (argc == 4) {
      kr_osc_enable (client, atoi(argv[3]));
    }
  }      

  if (strncmp(argv[2], "oscoff", 6) == 0) {
    if (argc == 3) {
      kr_osc_disable (client);
    }
  }

  /* Krad Mixer Commands */

  if (strncmp(argv[2], "lm", 2) == 0) {
    if (argc == 3) {
      kr_mixer_portgroup_list (client);
      kr_delivery_accept_and_report (client);
    }
  }

  if (((strncmp(argv[2], "m", 3) == 0) && (strlen(argv[2]) == 1)) ||
      ((strncmp(argv[2], "mix", 3) == 0) && (strlen(argv[2]) == 3)) ||
      ((strncmp(argv[2], "mixer", 5) == 0) && (strlen(argv[2]) == 5))) {
    if (argc == 3) {
      kr_mixer_info (client);
      kr_delivery_accept_and_report (client);
    }
  }      

  if (strncmp(argv[2], "setrate", 7) == 0) {
    if (argc == 4) {
      kr_mixer_set_sample_rate (client, atoi(argv[3]));
    }
  }        

  if (strncmp(argv[2], "tone", 4) == 0) {
    if (argc == 4) {
      kr_mixer_push_tone (client, argv[3]);
    }
  }

  if (strncmp(argv[2], "portinfo", 8) == 0) {
    if (argc == 4) {
      kr_mixer_portgroup_info (client, argv[3]);
      kr_delivery_accept_and_report (client);
    }
  }

  if (strncmp(argv[2], "input", 5) == 0) {
    if (argc == 4) {
      kr_mixer_create_portgroup (client, argv[3], "input", 2);
    }
    if (argc == 5) {
      kr_mixer_create_portgroup (client, argv[3], "input", atoi (argv[4]));
    }
  }      

  if (strncmp(argv[2], "output", 6) == 0) {
    if (argc == 4) {
      kr_mixer_create_portgroup (client, argv[3], "output", 2);
    }
    if (argc == 5) {
      kr_mixer_create_portgroup (client, argv[3], "output", atoi (argv[4]));
    }
  }
  
  if (strncmp(argv[2], "auxout", 6) == 0) {
    if (argc == 4) {
      kr_mixer_create_portgroup (client, argv[3], "auxout", 2);
    }
    if (argc == 5) {
      kr_mixer_create_portgroup (client, argv[3], "auxout", atoi (argv[4]));
    }
  }

  if (strncmp(argv[2], "plug", 4) == 0) {
    if (argc == 5) {
      kr_mixer_plug_portgroup (client, argv[3], argv[4]);
    }
  }

  if (strncmp(argv[2], "unplug", 6) == 0) {
    if (argc == 4) {
      kr_mixer_unplug_portgroup (client, argv[3], "");
    }
    if (argc == 5) {
      kr_mixer_unplug_portgroup (client, argv[3], argv[4]);
    }        
  }            

  if (strncmp(argv[2], "map", 3) == 0) {
    if (argc == 6) {
      kr_mixer_update_portgroup_map_channel (client, argv[3], atoi(argv[4]), atoi(argv[5]));
    }
  }

  if (strncmp(argv[2], "mixmap", 3) == 0) {
    if (argc == 6) {
      kr_mixer_update_portgroup_mixmap_channel (client, argv[3], atoi(argv[4]), atoi(argv[5]));
    }
  }      

  if (strncmp(argv[2], "crossfade", 9) == 0) {
    if (argc == 4) {
      kr_mixer_set_portgroup_crossfade_group (client, argv[3], "");
    }
    if (argc == 5) {
      kr_mixer_set_portgroup_crossfade_group (client, argv[3], argv[4]);
    }
  }
  
  if ((strncmp(argv[2], "rmcrossfade", 11) == 0) || (strncmp(argv[2], "nocrossfade", 11) == 0)) {
    if (argc == 4) {
      kr_mixer_set_portgroup_crossfade_group (client, argv[3], "");
    }
  }     

  if (strncmp(argv[2], "xmms2", 5) == 0) {
    if (argc == 5) {
      if ((strncmp(argv[4], "play", 4) == 0) || (strncmp(argv[4], "pause", 5) == 0) ||
        (strncmp(argv[4], "stop", 4) == 0) || (strncmp(argv[4], "next", 4) == 0) ||
        (strncmp(argv[4], "prev", 4) == 0)) {
        kr_mixer_portgroup_xmms2_cmd (client, argv[3], argv[4]);
        return 0;
      } else {
        kr_mixer_bind_portgroup_xmms2 (client, argv[3], argv[4]);
      }
    }
  }  

  if (strncmp(argv[2], "noxmms2", 7) == 0) {
    if (argc == 4) {
      kr_mixer_unbind_portgroup_xmms2 (client, argv[3]);
    }
  }

  if (strncmp(argv[2], "setmix", 6) == 0) {
    if (argc == 6) {
      kr_mixer_set_control (client, argv[3], argv[4], atof(argv[5]), 0);
    }
    if (argc == 7) {
      kr_mixer_set_control (client, argv[3], argv[4], atof(argv[5]), atoi(argv[6]));
    }
  }

  if (((argc == 5) || (argc == 6)) &&
      (((strlen(argv[2]) == 1) && (strncmp(argv[2], "s", 1) == 0)) ||
       ((strlen(argv[2]) == 3) && (strncmp(argv[2], "set", 3) == 0)))) {

    memset (&uc, 0, sizeof (uc));
    if (kr_string_to_address (argv[3], &uc.address)) {
      if (argc == 5) {
        uc.value.real = atof(argv[4]);
        uc.duration = 0;
      }
      if (argc == 6) {
        uc.value.real = atof(argv[4]);
        uc.duration = atoi(argv[5]);
      }
      kr_unit_control_set (client, &uc);
    }
  }
  
  if (((argc == 4) || (argc == 5)) &&
      (((strlen(argv[2]) > 2) && (strchr(argv[2], '/') != NULL)) ||
       (0))) {

    memset (&uc, 0, sizeof (uc));
    if (kr_string_to_address (argv[2], &uc.address)) {
      kr_unit_control_data_type_from_address (&uc.address, &uc.data_type);
      if (uc.data_type == KR_FLOAT) {
        uc.value.real = atof(argv[3]);
      }
      if (uc.data_type == KR_INT32) {
        uc.value.integer = atoi(argv[3]);
      }
      if (uc.data_type == KR_STRING) {
        uc.value.string = argv[3];
      }
      if (argc == 4) {
        uc.duration = 0;
      }
      if (argc == 5) {
        uc.duration = atoi(argv[4]);
      }
      kr_unit_control_set (client, &uc);
    }
  }
  
  if ((argc == 4) && ((strncmp(argv[2], "rm", 2) == 0) && (strlen(argv[2]) == 2)) &&
      (((strlen(argv[3]) > 2) && (strchr(argv[3], '/') != NULL)) ||
       (0))) {

    memset (&uc, 0, sizeof (uc));
    if (kr_string_to_address (argv[3], &uc.address)) {
      kr_unit_destroy (client, &uc.address);
    }
  }

  /* Krad Compositor Commands */

  if ((strncmp(argv[2], "lc", 2) == 0) && (strlen(argv[2]) == 2)) {
    if (argc == 3) {
      kr_compositor_subunit_list (client);
      kr_delivery_accept_and_report (client);
    }
  }
  
  if ((strlen(argv[2]) == 9) && (strncmp(argv[2], "addsprite", 9) == 0)) {
    if (argc == 4) {
      kr_compositor_subunit_create (client, KR_SPRITE, argv[3], NULL);
    }
  }
  
  if ((strlen(argv[2]) == 7) && (strncmp(argv[2], "addtext", 7) == 0)) {
    if (argc == 4) {
      kr_compositor_subunit_create (client, KR_TEXT, argv[3], NULL);
    }
    if (argc == 5) {
      kr_compositor_subunit_create (client, KR_TEXT, argv[3], argv[4]);
    }
  }
  
  if ((strlen(argv[2]) > 5) && (strncmp(argv[2], "addvec", 6) == 0)) {
    if (argc == 4) {
      kr_compositor_subunit_create (client, KR_VECTOR, argv[3], NULL);
    }
  }

  if (strncmp(argv[2], "snap", 4) == 0) {
    if (argc == 3) {
      kr_compositor_snapshot (client);
    }
  }

  if (strncmp(argv[2], "jsnap", 5) == 0) {
    if (argc == 3) {
      kr_compositor_snapshot_jpeg (client);
    }
  }
  
  if (strncmp(argv[2], "lastsnap", 8) == 0) {
    //FIXME
    //kr_compositor_info (client);
    //kr_delivery_accept_and_report (client);        
  }

  if ((strncmp(argv[2], "comp", 4) == 0) ||
      ((strncmp(argv[2], "c", 1) == 0) && (strlen(argv[2]) == 1))) {
    if (argc == 3) {
      kr_compositor_info (client);
      kr_delivery_accept_and_report (client);
    }
  }

  if (strncmp(argv[2], "res", 3) == 0) {
    if (argc == 5) {
      kr_compositor_set_resolution (client, atoi(argv[3]), atoi(argv[4]));
    }
  }

  if (strncmp(argv[2], "fps", 3) == 0) {
    if (argc == 4) {
      kr_compositor_set_frame_rate (client, atoi(argv[3]) * 1000, 1000);
    }      
    if (argc == 5) {
      kr_compositor_set_frame_rate (client, atoi(argv[3]), atoi(argv[4]));
    }
  }

  if (strncmp(argv[2], "background", 10) == 0) {
    if (argc == 4) {
      kr_compositor_background (client, argv[3]);
    }
  }      

  if (strncmp(argv[2], "display", 7) == 0) {
    if (argc == 3) {
      kr_compositor_open_display (client, 0, 0);
    }
    if (argc == 4) {
      kr_compositor_open_display (client, 1, 1);
    }          
    if (argc == 5) {
      kr_compositor_open_display (client, atoi(argv[3]), atoi(argv[4]));
    }        
  }

  if (strncmp(argv[2], "closedisplay", 12) == 0) {
    if (argc == 3) {
      kr_compositor_close_display (client);
    }
  }

  /* Krad Transponder Commands */      

  if ((strncmp(argv[2], "ll", 2) == 0) && (strlen(argv[2]) == 2)) {
    if (argc == 3) {
      //kr_transponder_list (client);
      //kr_delivery_accept_and_report (client);
    }
  }

  if (strncmp(argv[2], "receiver_on", 11) == 0) {
    if (argc == 4) {
      kr_transponder_receiver_enable (client, atoi(argv[3]));
    }
  }

  if (strncmp(argv[2], "receiver_off", 12) == 0) {
    if (argc == 3) {
      kr_transponder_receiver_disable (client);
    }
  }

  if (strncmp(argv[2], "transmitter_on", 14) == 0) {
    if (argc == 4) {
      kr_transponder_transmitter_enable (client, atoi(argv[3]));
    }
  }

  if (strncmp(argv[2], "transmitter_off", 15) == 0) {
    if (argc == 3) {
      kr_transponder_transmitter_disable (client);
    }
  }    

  if ((strncmp(argv[2], "link", 4) == 0) || (strncmp(argv[2], "transmit", 8) == 0)) {
    if (argc == 7) {
      if (strncmp(argv[2], "transmitav", 10) == 0) {
        kr_transponder_transmit (client, AUDIO_AND_VIDEO, argv[3], atoi(argv[4]), argv[5], argv[6], NULL, 0, 0, 0, "");
      } else {
        kr_transponder_transmit (client, AUDIO_ONLY, argv[3], atoi(argv[4]), argv[5], argv[6], NULL, 0, 0, 0, "");
      }
    }
    if (argc == 8) {
      kr_transponder_transmit (client, krad_link_string_to_av_mode (argv[3]), argv[4], atoi(argv[5]), argv[6], argv[7], NULL,
                       0, 0, 0, "");
    }

    if (argc == 9) {
      kr_transponder_transmit (client, krad_link_string_to_av_mode (argv[3]), argv[4], atoi(argv[5]), argv[6], argv[7], argv[8],
                       0, 0, 0, "");
    }

    if (argc == 10) {
      kr_transponder_transmit (client, krad_link_string_to_av_mode (argv[3]), argv[4], atoi(argv[5]), argv[6], argv[7], argv[8],
                       atoi(argv[9]), 0, 0, "");
    }

    if (argc == 11) {
      kr_transponder_transmit (client, krad_link_string_to_av_mode (argv[3]), argv[4], atoi(argv[5]), argv[6], argv[7], argv[8],
                               atoi(argv[9]), atoi(argv[10]), 0, "");
    }

    if (argc == 12) {
      kr_transponder_transmit (client, krad_link_string_to_av_mode (argv[3]), argv[4], atoi(argv[5]), argv[6], argv[7], argv[8],
                               atoi(argv[9]), atoi(argv[10]), atoi(argv[11]), "");
    }

    if (argc == 13) {
      kr_transponder_transmit (client, krad_link_string_to_av_mode (argv[3]), argv[4], atoi(argv[5]), argv[6], argv[7], argv[8],
                               atoi(argv[9]), atoi(argv[10]), atoi(argv[11]), argv[12]);
    }
  }

  if (strncmp(argv[2], "capture", 7) == 0) {

    if (krad_link_string_to_video_source (argv[3]) == DECKLINK) {
      val = AUDIO_AND_VIDEO;
    } else {
      val = VIDEO_ONLY;
    }

    if (argc == 4) {
      kr_transponder_capture (client, krad_link_string_to_video_source (argv[3]), "",
                      0, 0, 0, 0, val, "", "");
    }
    if (argc == 5) {
      kr_transponder_capture (client, krad_link_string_to_video_source (argv[3]), argv[4],
                      0, 0, 0, 0, val, "", "");
    }
    if (argc == 7) {
      kr_transponder_capture (client, krad_link_string_to_video_source (argv[3]), argv[4],
                      atoi(argv[5]), atoi(argv[6]), 0, 0, val, "", "");
    }
    if (argc == 9) {
      kr_transponder_capture (client, krad_link_string_to_video_source (argv[3]), argv[4],
                      atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), val, "", "");
    }
    if (argc == 10) {
      kr_transponder_capture (client, krad_link_string_to_video_source (argv[3]), argv[4],
                      atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]),
                      krad_link_string_to_av_mode (argv[9]), "", "");
    }
    if (argc == 11) {
      kr_transponder_capture (client, krad_link_string_to_video_source (argv[3]), argv[4],
                      atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]),
                      krad_link_string_to_av_mode (argv[9]), argv[10], "");
    }
    if (argc == 12) {
      kr_transponder_capture (client, krad_link_string_to_video_source (argv[3]), argv[4],
                      atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]),
                      krad_link_string_to_av_mode (argv[9]), argv[10], argv[11]);
    }
    usleep (100000);
  }

  if (strncmp(argv[2], "record", 6) == 0) {
    if (argc == 4) {
      if (strncmp(argv[2], "recordav", 8) == 0) {
        kr_transponder_record (client, AUDIO_AND_VIDEO, argv[3], NULL, 0, 0, 0, "");
      } else {
        kr_transponder_record (client, AUDIO_ONLY, argv[3], NULL, 0, 0, 0, "");
      }
    }
    if (argc == 5) {
      kr_transponder_record (client, krad_link_string_to_av_mode (argv[3]), argv[4], NULL,
                     0, 0, 0, "");
    }

    if (argc == 6) {
      kr_transponder_record (client, krad_link_string_to_av_mode (argv[3]), argv[4], argv[5],
                     0, 0, 0, "");
    }

    if (argc == 7) {
      kr_transponder_record (client, krad_link_string_to_av_mode (argv[3]), argv[4], argv[5],
                     atoi(argv[6]), 0, 0, "");
    }

    if (argc == 8) {
      kr_transponder_record (client, krad_link_string_to_av_mode (argv[3]), argv[4], argv[5],
                     atoi(argv[6]), atoi(argv[7]), 0, "");
    }

    if (argc == 9) {
      kr_transponder_record (client, krad_link_string_to_av_mode (argv[3]), argv[4], argv[5],
                     atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), "");
    }

    if (argc == 10) {
      kr_transponder_record (client, krad_link_string_to_av_mode (argv[3]), argv[4], argv[5],
                     atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), argv[9]);          
    }                                
  }

  if (strncmp(argv[2], "play", 4) == 0) {
    if (argc == 4) {
      kr_transponder_play (client, argv[3]);
    }
    if (argc == 6) {
      kr_transponder_play_remote (client, argv[3], atoi(argv[4]), argv[5] );
    }
  }

  if (strncmp(argv[2], "update", 2) == 0) {

    if (argc == 5) {
      if (strcmp(argv[4], "vp8_keyframe") == 0) {
        kr_transponder_update (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_VP8_FORCE_KEYFRAME, 1);
      }
    }

    if (argc == 6) {
      if (strcmp(argv[4], "vp8_bitrate") == 0) {
        kr_transponder_update (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_VP8_BITRATE, atoi(argv[5]));
      }
      if (strcmp(argv[4], "vp8_min_quantizer") == 0) {
        kr_transponder_update (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_VP8_MIN_QUANTIZER, atoi(argv[5]));
      }
      if (strcmp(argv[4], "vp8_max_quantizer") == 0) {
        kr_transponder_update (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_VP8_MAX_QUANTIZER, atoi(argv[5]));
      }
      if (strcmp(argv[4], "vp8_deadline") == 0) {
        kr_transponder_update (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_VP8_DEADLINE, atoi(argv[5]));
      }
      if (strcmp(argv[4], "theora_quality") == 0) {
        kr_transponder_update (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_THEORA_QUALITY, atoi(argv[5]));
      }                                      
      if (strcmp(argv[4], "opus_bitrate") == 0) {
        kr_transponder_update (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_OPUS_BITRATE, atoi(argv[5]));
      }        
      if (strcmp(argv[4], "opus_bandwidth") == 0) {
        kr_transponder_update_str (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_OPUS_BANDWIDTH, argv[5]);
      }
      if (strcmp(argv[4], "opus_signal") == 0) {
        kr_transponder_update_str (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_OPUS_SIGNAL, argv[5]);
      }
      if (strcmp(argv[4], "opus_complexity") == 0) {
        kr_transponder_update (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_OPUS_COMPLEXITY, atoi(argv[5]));
      }
      if (strcmp(argv[4], "opus_framesize") == 0) {
        kr_transponder_update (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_OPUS_FRAME_SIZE, atoi(argv[5]));
      }                    
      if (strcmp(argv[4], "ogg_maxpackets") == 0) {
        kr_transponder_update (client, atoi(argv[3]), EBML_ID_KRAD_LINK_LINK_OGG_MAX_PACKETS_PER_PAGE, atoi(argv[5]));
      }
    }
  }

  kr_client_destroy (&client);

  return 0;

}
