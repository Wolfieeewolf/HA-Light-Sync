# Home Assistant Plugin for OpenRGB

A Home Assistant integration plugin for OpenRGB that allows you to control your Home Assistant lights directly through the OpenRGB interface, enabling seamless synchronization between your PC RGB devices and smart home lighting.

## Project Background

This plugin bridges the gap between OpenRGB's PC-focused RGB control and Home Assistant's smart home lighting capabilities. It allows users to incorporate their smart home lighting into their PC RGB ecosystem, creating a unified lighting control system.

## Development Note

This entire plugin was created using assistance from:
- [Claude AI](https://claude.ai)
- [ChatGPT](https://chat.openai.com)
- [DeepSeek](https://www.deepseek.com/)

As such:
- This is a very early alpha version
- There may be bugs and issues
- Some features might not work as expected
- Error handling might be basic

## Features

- Direct Integration: Connect directly to your Home Assistant instance
- Auto-Discovery: Automatically finds compatible lights in your Home Assistant setup
- Real-time Control: Instant response to lighting changes
- Persistent Settings: Saves your configuration and device selections
- Device Management: Add or remove lights easily

## Installation

1. Download the plugin file (HA Light Sync.dll)
3. Place it in your OpenRGB plugins folder:
   - Windows: `%APPDATA%\OpenRGB\plugins`
   - Linux: `~/.config/OpenRGB/plugins`
4. Run OpenRGB
5. Configure your Home Assistant connection:
   - Enter your Home Assistant URL
   - Add your Long-Lived Access Token
   - Select the lights you want to control

## Open Source and Collaboration

Feel free to fork this repository and modify it however you like! This project is meant to be:
- An experiment in AI-assisted development
- A learning resource for others
- A foundation for community improvements
- Open to any and all modifications

If you're interested in the intersection of AI and development, this project serves as a real-world example of what's possible.

## Development Status

This plugin is in early alpha stage. While core functionality works, expect some rough edges. Please report any issues or feature requests through GitHub issues, but understand that as this is an AI-assisted project, fixes and updates may take time as we experiment with the best ways to implement changes.

## Supporting Development

This project is developed using AI assistance, which involves subscription and API costs. If you find the Home Assistant Plugin useful and would like to support its continued development, you're welcome to contribute via:

<a href="https://www.buymeacoffee.com/Wolfieee"><img src="https://img.buymeacoffee.com/button-api/?text=Buy me a pizza&emoji=🍕&slug=Wolfieee&button_colour=40DCA5&font_colour=ffffff&font_family=Poppins&outline_colour=000000&coffee_colour=FFDD00" /></a>

Your support helps maintain the AI tools that make this development possible, but the plugin will always remain free and open source regardless.

## License

This project is open-source software. Feel free to experiment, modify, and improve upon it!
