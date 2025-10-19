import pygame
import random
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
PLAYER_SPEED = 5
BLOCK_SIZE = 50
BLOCK_SPEED = 5
SPAWN_EVENT = pygame.USEREVENT + 1
class Player(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.Surface((100, 20))
        self.image.fill((0, 200, 0))
        self.rect = self.image.get_rect(midbottom=(SCREEN_WIDTH//2, SCREEN_HEIGHT - 10))
    def update(self):
        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT] and self.rect.left > 0:
            self.rect.x -= PLAYER_SPEED
        if keys[pygame.K_RIGHT] and self.rect.right < SCREEN_WIDTH:
            self.rect.x += PLAYER_SPEED
class Block(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.Surface((BLOCK_SIZE, BLOCK_SIZE))
        self.image.fill((200, 0, 0))
        self.rect = self.image.get_rect(midtop=(random.randint(0, SCREEN_WIDTH - BLOCK_SIZE), 0))
    def update(self):
        self.rect.y += BLOCK_SPEED
        if self.rect.top > SCREEN_HEIGHT:
            self.kill()
def main():
    pygame.init()
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("Catch the Blocks")
    clock = pygame.time.Clock()
    score = 0    
    player_group = pygame.sprite.GroupSingle(Player())
    block_group = pygame.sprite.Group()
    pygame.time.set_timer(SPAWN_EVENT, 1000)
    font = pygame.font.Font(None, 36)
    running = True    
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False            
            elif event.type == SPAWN_EVENT:
                block_group.add(Block())
        player_group.update()
        block_group.update()
        collisions = pygame.sprite.groupcollide(block_group, player_group, True, False)
        if collisions:
            score += len(collisions)
        screen.fill((30, 30, 30))
        player_group.draw(screen)
        block_group.draw(screen)
        score_text = font.render(f"Score: {score}", True, (255,255,255))
        screen.blit(score_text, (10, 10))
        pygame.display.flip()
        clock.tick(60)
    pygame.quit()
if __name__ == "__main__":
    main()