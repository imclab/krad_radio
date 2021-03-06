#include "krad_compositor_interface.h"

void krad_compositor_videoport_rep_to_ebml (kr_port_t *port, krad_ebml_t *ebml);
void krad_compositor_text_rep_to_ebml (krad_text_rep_t *text, krad_ebml_t *ebml);
void krad_compositor_sprite_rep_to_ebml (krad_sprite_rep_t *sprite, krad_ebml_t *ebml);
void krad_compositor_vector_rep_to_ebml (krad_vector_rep_t *vector, krad_ebml_t *ebml);

void krad_compositor_videoport_rep_to_ebml2 (kr_port_t *port, kr_ebml2_t *ebml) {

  kr_ebml2_pack_string (ebml, EBML_ID_KRAD_COMPOSITOR_TEXT, port->sysname);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, port->direction);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, port->controls.x);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->controls.y);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->controls.z);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->source_width);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->source_height);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->crop_x);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->crop_y);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->crop_width);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->crop_height);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->controls.width);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->controls.height);  
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_OPACITY, port->controls.opacity);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_ROTATION, port->controls.rotation);
}

void krad_compositor_text_rep_to_ebml2 (krad_text_rep_t *text, kr_ebml2_t *ebml) {

  kr_ebml2_pack_string (ebml, EBML_ID_KRAD_COMPOSITOR_TEXT, text->text);
  kr_ebml2_pack_string (ebml, EBML_ID_KRAD_COMPOSITOR_FONT, text->font);
  
  kr_ebml2_pack_float (ebml,
                         EBML_ID_KRAD_COMPOSITOR_RED,
                         text->red);
  kr_ebml2_pack_float (ebml,
                         EBML_ID_KRAD_COMPOSITOR_GREEN,
                         text->green);
  kr_ebml2_pack_float (ebml,
                         EBML_ID_KRAD_COMPOSITOR_BLUE,
                         text->blue);

  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, text->controls.x);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, text->controls.y);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, text->controls.z);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, text->controls.width);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, text->controls.height);  
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_SCALE, text->controls.xscale);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_OPACITY, text->controls.opacity);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_ROTATION, text->controls.rotation);
}

void krad_compositor_videoport_rep_to_ebml (kr_port_t *port, krad_ebml_t *ebml) {

  krad_ebml_write_string (ebml, EBML_ID_KRAD_COMPOSITOR_TEXT, port->sysname);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, port->direction);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, port->controls.x);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->controls.y);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->controls.z);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->source_width);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->source_height);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->crop_x);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->crop_y);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->crop_width);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->crop_height);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->controls.width);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, port->controls.height);  
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_OPACITY, port->controls.opacity);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_ROTATION, port->controls.rotation);
}

void krad_compositor_text_rep_to_ebml (krad_text_rep_t *text, krad_ebml_t *ebml) {

  krad_ebml_write_string (ebml, EBML_ID_KRAD_COMPOSITOR_TEXT, text->text);
  krad_ebml_write_string (ebml, EBML_ID_KRAD_COMPOSITOR_FONT, text->font);
  
  krad_ebml_write_float (ebml,
                         EBML_ID_KRAD_COMPOSITOR_RED,
                         text->red);
  krad_ebml_write_float (ebml,
                         EBML_ID_KRAD_COMPOSITOR_GREEN,
                         text->green);
  krad_ebml_write_float (ebml,
                         EBML_ID_KRAD_COMPOSITOR_BLUE,
                         text->blue);

  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, text->controls.x);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, text->controls.y);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, text->controls.z);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, text->controls.width);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, text->controls.height);  
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_SCALE, text->controls.xscale);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_OPACITY, text->controls.opacity);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_ROTATION, text->controls.rotation);
}

void krad_compositor_sprite_rep_to_ebml (krad_sprite_rep_t *sprite, krad_ebml_t *ebml) {
  krad_ebml_write_string (ebml, EBML_ID_KRAD_COMPOSITOR_FILENAME, sprite->filename);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, sprite->controls.x);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, sprite->controls.y);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, sprite->controls.z);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_TICKRATE, sprite->controls.tickrate);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_SCALE, sprite->controls.xscale);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_SCALE, sprite->controls.yscale);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_OPACITY, sprite->controls.opacity);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_ROTATION, sprite->controls.rotation);
}

void krad_compositor_sprite_rep_to_ebml2 (krad_sprite_rep_t *sprite, kr_ebml2_t *ebml) {
  kr_ebml2_pack_string (ebml, EBML_ID_KRAD_COMPOSITOR_FILENAME, sprite->filename);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, sprite->controls.x);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, sprite->controls.y);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, sprite->controls.z);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_TICKRATE, sprite->controls.tickrate);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_SCALE, sprite->controls.xscale);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_SCALE, sprite->controls.yscale);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_OPACITY, sprite->controls.opacity);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_ROTATION, sprite->controls.rotation);
}

void krad_compositor_vector_rep_to_ebml (krad_vector_rep_t *vector, krad_ebml_t *ebml) {
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, vector->type);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, vector->controls.width);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, vector->controls.height);  
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, vector->controls.x);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, vector->controls.y);
  krad_ebml_write_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, vector->controls.z);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_SCALE, vector->controls.xscale);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_SCALE, vector->controls.yscale);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_OPACITY, vector->controls.opacity);
  krad_ebml_write_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_ROTATION, vector->controls.rotation);
}

void krad_compositor_vector_rep_to_ebml2 (krad_vector_rep_t *vector, kr_ebml2_t *ebml) {
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, vector->type);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, vector->controls.width);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, vector->controls.height);  
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_X, vector->controls.x);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, vector->controls.y);
  kr_ebml2_pack_int32 (ebml, EBML_ID_KRAD_COMPOSITOR_Y, vector->controls.z);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_SCALE, vector->controls.xscale);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_SCALE, vector->controls.yscale);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_OPACITY, vector->controls.opacity);
  kr_ebml2_pack_float (ebml, EBML_ID_KRAD_COMPOSITOR_SPRITE_ROTATION, vector->controls.rotation);
}

int krad_videoport_to_rep (krad_compositor_port_t *videoport, kr_port_t *videoport_rep) {
  
  if ((videoport == NULL) || (videoport_rep == NULL)) {
    return 0;
  }

  strncpy (videoport_rep->sysname, videoport->sysname, sizeof(videoport_rep->sysname));

  videoport_rep->direction = videoport->direction;

  videoport_rep->controls.x = videoport->subunit.x;
  videoport_rep->controls.y = videoport->subunit.y;
  videoport_rep->controls.z = videoport->subunit.z;
 
  videoport_rep->source_width = videoport->source_width;
  videoport_rep->source_height = videoport->source_height;
  
  videoport_rep->crop_x = videoport->crop_x;
  videoport_rep->crop_y = videoport->crop_y;
  
  videoport_rep->crop_width = videoport->crop_width;
  videoport_rep->crop_height = videoport->crop_height;
 
 
  
  videoport_rep->controls.width = videoport->subunit.width;
  videoport_rep->controls.height = videoport->subunit.height;
    
  videoport_rep->controls.rotation = videoport->subunit.rotation;
  videoport_rep->controls.opacity = videoport->subunit.opacity;
   
  return 1;
}

void krad_compositor_sprite_to_ebml2 ( kr_ebml2_t *ebml, krad_sprite_t *sprite ) {
  krad_sprite_rep_t sprite_rep;
  krad_sprite_to_rep (sprite, &sprite_rep);
  krad_compositor_sprite_rep_to_ebml2 (&sprite_rep, ebml);
}

void krad_compositor_text_to_ebml2 ( kr_ebml2_t *ebml, krad_text_t *text ) {
  krad_text_rep_t text_rep;
  krad_text_to_rep (text, &text_rep);
  krad_compositor_text_rep_to_ebml2 (&text_rep, ebml);
}

void krad_compositor_vector_to_ebml2 ( kr_ebml2_t *ebml, krad_vector_t *vector ) {
  krad_vector_rep_t vector_rep;
  krad_vector_to_rep (vector, &vector_rep);
  krad_compositor_vector_rep_to_ebml2 (&vector_rep, ebml);
}

void krad_compositor_videoport_to_ebml2 ( kr_ebml2_t *ebml, krad_compositor_port_t *videoport ) {
  kr_port_t videoport_rep;
  krad_videoport_to_rep (videoport, &videoport_rep);
  krad_compositor_videoport_rep_to_ebml2 (&videoport_rep, ebml);
}


void krad_compositor_sprite_to_ebml ( krad_ipc_server_t *krad_ipc, krad_sprite_t *sprite ) {
  krad_sprite_rep_t sprite_rep;
  krad_sprite_to_rep (sprite, &sprite_rep);
  krad_compositor_sprite_rep_to_ebml (&sprite_rep, krad_ipc->current_client->krad_ebml2);
}

void krad_compositor_vector_to_ebml ( krad_ipc_server_t *krad_ipc, krad_vector_t *vector ) {
  krad_vector_rep_t vector_rep;
  krad_vector_to_rep (vector, &vector_rep);
  krad_compositor_vector_rep_to_ebml (&vector_rep, krad_ipc->current_client->krad_ebml2);
}

void krad_compositor_text_to_ebml ( krad_ipc_server_t *krad_ipc, krad_text_t *text ) {
  krad_text_rep_t text_rep;
  krad_text_to_rep (text, &text_rep);
  krad_compositor_text_rep_to_ebml (&text_rep, krad_ipc->current_client->krad_ebml2);
}

void krad_compositor_videoport_to_ebml ( krad_ipc_server_t *krad_ipc, krad_compositor_port_t *videoport ) {
  kr_port_t videoport_rep;
  krad_videoport_to_rep (videoport, &videoport_rep);
  krad_compositor_videoport_rep_to_ebml (&videoport_rep, krad_ipc->current_client->krad_ebml2);
}

int krad_compositor_handler ( krad_compositor_t *krad_compositor, krad_ipc_server_t *krad_ipc ) {
  
  uint32_t ebml_id;
  uint32_t command;
  uint64_t ebml_data_size;
  kr_address_t address;
  kr_unit_control_t unit_control;
  uint64_t response;
  uint64_t payload_loc;
  uint64_t numbers[4];
  int nums[4];
  int type;
  int p;
  int s;
  int sd1;
  int sd2;
  char string[256];
  char string2[256];

  type = 0;
  sd1 = 0;
  sd2 = 0;  
  p = 0;
  s = 0;
  string[0] = '\0';
  string2[0] = '\0';

  krad_ipc_server_read_command ( krad_ipc, &command, &ebml_data_size);

  switch ( command ) {
    case EBML_ID_KRAD_COMPOSITOR_CMD_SET_SUBUNIT:
      unit_control.address.path.unit = KR_COMPOSITOR;
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      numbers[0] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      unit_control.address.path.subunit.compositor_subunit = numbers[0];
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      numbers[0] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      unit_control.address.id.number = numbers[0];
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      numbers[0] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      unit_control.address.control.compositor_control = numbers[0];
      kr_unit_control_data_type_from_address (&unit_control.address, &unit_control.data_type);
      if (unit_control.data_type == KR_FLOAT) {
        krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
        unit_control.value.real = krad_ebml_read_float (krad_ipc->current_client->krad_ebml, ebml_data_size);
      }
      if (unit_control.data_type == KR_INT32) {
        krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
        unit_control.value.integer = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      }
      if (unit_control.data_type == KR_STRING) {
        //bah
      }
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      unit_control.duration = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      numbers[1] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      krad_compositor_subunit_update (krad_compositor, &unit_control);

      if (unit_control.data_type == KR_FLOAT) {
        krad_radio_broadcast_subunit_update ( krad_ipc->ipc_broadcaster, &unit_control.address, unit_control.address.control.compositor_control,
                                              unit_control.data_type, (void *)&unit_control.value.real, krad_ipc->current_client );
      }
      if (unit_control.data_type == KR_INT32) {
        krad_radio_broadcast_subunit_update ( krad_ipc->ipc_broadcaster, &unit_control.address, unit_control.address.control.compositor_control,
                                              unit_control.data_type, (void *)&unit_control.value.integer, krad_ipc->current_client );
      }
      
      break;  
    case EBML_ID_KRAD_COMPOSITOR_CMD_REMOVE_SUBUNIT:
      address.path.unit = KR_COMPOSITOR;
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      numbers[0] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      address.path.subunit.compositor_subunit = numbers[0];
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      numbers[0] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      address.id.number = numbers[0];
      if (krad_compositor_subunit_destroy (krad_compositor, &address)) {
        krad_radio_broadcast_subunit_destroyed (krad_ipc->ipc_broadcaster, &address);
      }
      break;
    case EBML_ID_KRAD_COMPOSITOR_CMD_ADD_SUBUNIT:
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      numbers[0] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      type = numbers[0];
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      krad_ebml_read_string (krad_ipc->current_client->krad_ebml, string, ebml_data_size);
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      krad_ebml_read_string (krad_ipc->current_client->krad_ebml, string2, ebml_data_size);
      s = krad_compositor_subunit_create (krad_compositor, type, string, string2);
      if (s > -1) {
        if (type == KR_SPRITE) {
          krad_radio_broadcast_subunit_created ( krad_ipc->ipc_broadcaster,
                                                 &krad_compositor->sprite[s].subunit.address,
                                                 (void *)&krad_compositor->sprite[s]);        
        }
        if (type == KR_TEXT) {
          krad_radio_broadcast_subunit_created ( krad_ipc->ipc_broadcaster,
                                                 &krad_compositor->text[s].subunit.address,
                                                 (void *)&krad_compositor->text[s]);        
        }
        if (type == KR_VECTOR) {
          krad_radio_broadcast_subunit_created ( krad_ipc->ipc_broadcaster,
                                                 &krad_compositor->vector[s].subunit.address,
                                                 (void *)&krad_compositor->vector[s]);        
        }
      }
      break;
    case EBML_ID_KRAD_COMPOSITOR_CMD_LIST_SUBUNITS:
      for (s = 0; s < KC_MAX_SPRITES; s++) {
        if (krad_compositor->sprite[s].subunit.active == 1) {
          krad_ipc_server_response_start_with_address_and_type ( krad_ipc,
                                                                 &krad_compositor->sprite[s].subunit.address,
                                                                 EBML_ID_KRAD_SUBUNIT_INFO,
                                                                 &response);
          krad_ipc_server_payload_start ( krad_ipc, &payload_loc);
          krad_compositor_sprite_to_ebml ( krad_ipc, &krad_compositor->sprite[s]);
          krad_ipc_server_payload_finish ( krad_ipc, payload_loc );
          krad_ipc_server_response_finish ( krad_ipc, response );
        }
      }
      for (s = 0; s < KC_MAX_TEXTS; s++) {
        if (krad_compositor->text[s].subunit.active == 1) {
          krad_ipc_server_response_start_with_address_and_type ( krad_ipc,
                                                                 &krad_compositor->text[s].subunit.address,
                                                                 EBML_ID_KRAD_SUBUNIT_INFO,
                                                                 &response);
          krad_ipc_server_payload_start ( krad_ipc, &payload_loc);
          krad_compositor_text_to_ebml ( krad_ipc, &krad_compositor->text[s]);
          krad_ipc_server_payload_finish ( krad_ipc, payload_loc );
          krad_ipc_server_response_finish ( krad_ipc, response );
        }
      }
      for (s = 0; s < KC_MAX_VECTORS; s++) {
        if (krad_compositor->vector[s].subunit.active == 1) {
          krad_ipc_server_response_start_with_address_and_type ( krad_ipc,
                                                                 &krad_compositor->vector[s].subunit.address,
                                                                 EBML_ID_KRAD_SUBUNIT_INFO,
                                                                 &response);
          krad_ipc_server_payload_start ( krad_ipc, &payload_loc);
          krad_compositor_vector_to_ebml ( krad_ipc, &krad_compositor->vector[s]);
          krad_ipc_server_payload_finish ( krad_ipc, payload_loc );
          krad_ipc_server_response_finish ( krad_ipc, response );
        }
      }
      for (s = 0; s < KC_MAX_PORTS; s++) {
        if (krad_compositor->port[s].subunit.active == 1) {
          krad_ipc_server_response_start_with_address_and_type ( krad_ipc,
                                                                 &krad_compositor->port[s].subunit.address,
                                                                 EBML_ID_KRAD_SUBUNIT_INFO,
                                                                 &response);
          krad_ipc_server_payload_start ( krad_ipc, &payload_loc);
          krad_compositor_videoport_to_ebml ( krad_ipc, &krad_compositor->port[s]);
          krad_ipc_server_payload_finish ( krad_ipc, payload_loc );
          krad_ipc_server_response_finish ( krad_ipc, response );
        }
      }
      return 1;
    case EBML_ID_KRAD_COMPOSITOR_CMD_INFO:
      krad_ipc_server_response_start_with_address_and_type ( krad_ipc,
                                                             &krad_compositor->address,
                                                             EBML_ID_KRAD_UNIT_INFO,
                                                             &response);

      krad_ipc_server_payload_start ( krad_ipc, &payload_loc);
      krad_ipc_server_respond_number ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_WIDTH, krad_compositor->width);
      krad_ipc_server_respond_number ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_HEIGHT, krad_compositor->height);  
      krad_ipc_server_respond_number ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_FPS_NUMERATOR,
                                       krad_compositor->fps_numerator);
      krad_ipc_server_respond_number ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_FPS_DENOMINATOR,
                                       krad_compositor->fps_denominator);
      krad_ipc_server_respond_number ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_SPRITE_COUNT,
                                       krad_compositor->active_sprites);
      krad_ipc_server_respond_number ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_TEXT_COUNT,
                                       krad_compositor->active_texts);
      krad_ipc_server_respond_number ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_VECTOR_COUNT,
                                       krad_compositor->active_vectors);
      krad_ipc_server_respond_number ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_PORT_COUNT,
                                       krad_compositor->active_input_ports);
      krad_ipc_server_respond_number ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_PORT_COUNT,
                                       krad_compositor->active_output_ports);
      krad_ipc_server_respond_number ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_PORT_COUNT,
                                       krad_compositor->frames);
      if (krad_compositor_get_background_name (krad_compositor, string)) {
        krad_ipc_server_respond_string ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_LAST_SNAPSHOT_NAME, string);
      } else {
        krad_ipc_server_respond_string ( krad_ipc, EBML_ID_KRAD_COMPOSITOR_LAST_SNAPSHOT_NAME, "");
      }
      krad_ipc_server_payload_finish ( krad_ipc, payload_loc );
      krad_ipc_server_response_finish ( krad_ipc, response );
      return 1;
    case EBML_ID_KRAD_COMPOSITOR_CMD_SET_FRAME_RATE:
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      nums[0] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      nums[1] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      printke ("Krad Compositor: FIXME Set frame rate - %d / %d", nums[0], nums[1]);
      break;
    case EBML_ID_KRAD_COMPOSITOR_CMD_SET_RESOLUTION:
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      nums[2] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);
      nums[3] = krad_ebml_read_number (krad_ipc->current_client->krad_ebml, ebml_data_size);
      printke ("Krad Compositor: FIXME Set resolution - %d x %d", nums[2], nums[3]);
      break;
    case EBML_ID_KRAD_COMPOSITOR_CMD_SET_BACKGROUND:
      krad_ebml_read_element (krad_ipc->current_client->krad_ebml, &ebml_id, &ebml_data_size);  
      krad_ebml_read_string (krad_ipc->current_client->krad_ebml, string, ebml_data_size);
      krad_compositor_set_background (krad_compositor, string);
      break;      
    case EBML_ID_KRAD_COMPOSITOR_CMD_LOCAL_VIDEOPORT_DESTROY:
      for (p = 0; p < KC_MAX_PORTS; p++) {
        if (krad_compositor->port[p].local == 1) {
          krad_compositor_port_destroy (krad_compositor, &krad_compositor->port[p]);
          break;
        }
      }
      break;
    case EBML_ID_KRAD_COMPOSITOR_CMD_LOCAL_VIDEOPORT_CREATE:
      sd1 = krad_ipc_server_recvfd (krad_ipc->current_client);
      sd2 = krad_ipc_server_recvfd (krad_ipc->current_client);
      printk ("VIDEOPORT_CREATE Got FD's %d and %d\n", sd1, sd2);
      krad_compositor_local_port_create (krad_compositor, "localport", INPUT, sd1, sd2);
      break;
  }
  return 0;
}

